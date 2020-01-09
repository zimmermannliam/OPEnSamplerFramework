#pragma once
#include <KPArray.hpp>
#include <KPFoundation.hpp>
#include <functional>

#define KPActionNameSize 20

class KPAction {
public:
    unsigned long startTime = 0;
    unsigned long delay     = 0;
    int repeat              = 1;
public:
    std::function<void()> callback;
	KPLocalString<20> name{"Undefined"};
    bool _enabled = false;

    KPAction() {}

    KPAction(std::function<void()> callback)
        : callback(callback) {
    }

    KPAction(unsigned long delay, std::function<void()> callback)
        : delay(delay), callback(callback) {
    }

    KPAction(unsigned long delay, std::function<void()> callback, KPLocalString<20> name)
        : delay(delay), callback(callback), name(name) {
    }

    void start(unsigned long currentTime) {
        startTime = currentTime;
        _enabled  = true;
    }

	void activate() {
		callback();
		repeat = std::max(repeat - 1, -1);
	}

    void stop() {
        _enabled = false;
    }

    bool enabled() const {
        return _enabled && repeat;
    }

    unsigned long timeElapsed(unsigned long currentTime) const {
        return currentTime - startTime;
    }
};

template <size_t N>
class KPActionChain {
private:
    KPArray<KPAction, N> _actions;

public:
    KPActionChain<N>() {}
    KPActionChain & delay(unsigned long delay, std::function<void()> callback) {
		unsigned long prevDelay = _actions ? _actions[_actions.size() - 1].delay : 0;
        _actions.append(KPAction(prevDelay + delay, callback, KPLocalString<20>("Action", "[", _actions.size(), "]")));
        return *this;
    }

    KPActionChain & then(std::function<void()> callback) {
		unsigned long prevDelay = _actions ? _actions[_actions.size() - 1].delay : 0;
        _actions.append(KPAction(prevDelay, callback, KPLocalString<20>("Action", "[", _actions.size(), "]")));
        return *this;
    }

    KPArray<KPAction, N> & actions() {
        return _actions;
    }
};

template <size_t N = 10>
class KPActionScheduler : public KPComponent {
private:
    KPArray<KPAction, N> buffer;

public:
    KPActionScheduler(const char * name)
        : KPComponent(name) {}

    void setup() override {

    }

    void execute() {

    }

    void remove() {

    }

    void update() override {
		for (int i = 0; i < (int) buffer.size(); i++) {
			auto & action = buffer[i];
			// println(action.name);
			if (action.timeElapsed(millis()) >= action.delay && action.enabled()) {
                action.activate();
				action.start(millis());
            }
		}

		if (buffer) {
			buffer.removeWithCondition([](const KPAction & action) {
				return !action.enabled();
			});
		}
    }

    void schedule(KPAction action) {
		action.start(millis());
        buffer.append(action);
    }
};

template <size_t N>
void run(KPAction & action, KPActionScheduler<N> & scheduler) {
}

template <size_t N>
void runForever(KPAction & action, KPActionScheduler<N> & scheduler) {
}

template <size_t K, size_t N>
void run(KPActionChain<K> & chain, KPActionScheduler<N> & scheduler) {
    for (KPAction & c : chain.actions()) {
        scheduler.schedule(c);
    }
}

template <size_t K, size_t N>
void runForever(KPActionChain<K> & chain, KPActionScheduler<N> & scheduler) {
    for (KPAction & c : chain.actions()) {
        scheduler.schedule(c);
    }
}