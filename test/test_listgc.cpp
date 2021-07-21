/*
 * test_listgc.cpp
 *
 *  Created on: 18 juin 2020
 *      Author: casse
 */

#include <elm/alloc/ListGC.h>
#include <elm/data/List.h>
#include <elm/sys/System.h>
#include <elm/test.h>

using namespace elm;

class Int {
public:
	inline Int(int x): i(x) { }
	int i;
};

class Provider: public GCManager {
public:

	Provider(): used_err(false), unk_err(false), cnt(0), gc(*this, 16), ending(false) {}

	~Provider() {
	}

	void add(Int *i) {
		used.add(i);
		//cerr << "DEBUG: add " << i->i << " (" << i << ")" << io::endl;
	}

	void remove(Int *i) {
		used.remove(i);
		removed.add(i);
		//cerr << "DEBUG: remove " << i->i << " (" << i << ")"  << io::endl;
	}

	void collect(AbstractGC& gc) override {
		cnt++;
		for(auto p: used)
			gc.mark(p, sizeof(Int));
	}

	void clean(void *p) override {
		//cerr << "DEBUG: clean " << reinterpret_cast<Int *>(p)->i << " (" << p << ")"  << io::endl;
		if(ending)
			return;
		Int *i = static_cast<Int *>(p);
		if(removed.contains(i))
			removed.remove(i);
		else if(used.contains(i)) {
			used_err = true;
			//cerr << "DEBUG: still in use!\n";
		}
		else {
			unk_err = true;
			//cerr << "DEBUG: don't know this block.\n";
		}
	}

	void run(int ss, bool only_alloc = false) {
		for(int i = 0; i < ss; i++) {
			auto c = sys::System::random(100);
			if(!used || c < 50 || only_alloc)
				add(new(gc.alloc<Int>()) Int(i));
			else
				remove(used[sys::System::random(used.length())]);
			if(used_err || unk_err)
				return;
		}
	}

	Vector<Int *> used;
	Vector<Int *> removed;
	bool used_err, unk_err;
	int cnt;
	ListGC gc;
	bool ending;
};

TEST_BEGIN(listgc)

	{
		Provider prov;
		prov.run(10);
		CHECK(!prov.used_err);
		CHECK(!prov.unk_err);
		CHECK(prov.cnt == 0);
	}

	{
		Provider prov;
		prov.run(15);
		prov.gc.runGC();
		CHECK(!prov.used_err);
		CHECK(!prov.unk_err);
		CHECK(prov.cnt == 1);
		CHECK(!prov.removed);
	}

	{
		Provider prov;
		prov.run(17, true);
		CHECK(!prov.used_err);
		CHECK(!prov.unk_err);
		CHECK(prov.cnt == 1);
	}

	{
		Provider prov;
		prov.run(10000);
		CHECK(!prov.used_err);
		CHECK(!prov.unk_err);
		prov.gc.runGC();
		CHECK(!prov.removed);
		cerr << "GC: " << prov.cnt << io::endl;
	}

TEST_END
