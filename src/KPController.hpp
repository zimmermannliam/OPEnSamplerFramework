#pragma once
#include <Array>
#include <KPFoundation.hpp>
#include <map>

class KPController {
private:
	std::map<const char *, KPComponent *> componentsByName;

public:
	virtual void setup() {}
	virtual void update() {
		for (auto & p : componentsByName) {
			p.second->update();
		}
	}

	void addComponent(KPComponent & c) {
		addComponent(&c);
	}

	void addComponent(KPComponent * c) {
		componentsByName[c->name] = c;
		c->controller			  = this;
		c->setup();
	}

	template <typename T>
	T * getComponent(const char * name) {
		auto c = componentsByName[name];
		if (c && c->enabled()) {
			return static_cast<T *>(c);
		}

		return nullptr;
	}
};