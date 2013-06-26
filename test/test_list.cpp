/*
 * test_list.cpp
 *
 *  Created on: 26 juin 2013
 *      Author: casse
 */

#include <elm/util/test.h>
#include <elm/imm/list.h>
#include <elm/genstruct/Vector.h>

using namespace elm;

#define NUM		10000
#define LOG(x)	cerr << x << io::endl

class MultiplyWithCarryGenerator {
public:
	inline MultiplyWithCarryGenerator(t::uint32 seed) { setSeed(seed); }
	t::uint32 next(void) {
		m_z = 36969 * (m_z & 0xffff) + (m_z >> 16);
		m_w = 18000 * (m_w & 0xffff) + (m_w >> 16);
		return (m_z << 16) + m_w;
	}
	inline t::uint32 seed(void) const { return (m_z << 16) + m_w; }
	inline void setSeed(t::uint32 seed) { m_z = seed >> 16; m_w = seed & 0xffff; }

private:
	t::uint32 m_z, m_w;
};


static imm::list<int> l;
static genstruct::Vector<imm::list<int> > lists;
static genstruct::Vector<genstruct::Vector<int> > vecs;
class MyGC: public imm::ListGC<int> {
protected:
	virtual void collect(void) {
		LOG("INFO: collecting garbage !");
		mark(l);
		for(int i = 0; i < lists.count(); i++)
			mark(lists[i]);
	}
};

TEST_BEGIN(list)

	MyGC gc;

	// simple test
	{
		CHECK(l.isEmpty());
		CHECK(l.length() == 0);
		l = gc.cons(100, l);
		CHECK(!l.isEmpty());
		CHECK(l.contains(100));
		CHECK(l.length() == 1);
		l = gc.cons(0, l);
		CHECK(!l.isEmpty());
		CHECK(l.contains(0));
		CHECK(l.contains(100));
		CHECK(l.length() == 2);
		l = l.tl();
		CHECK(!l.isEmpty());
		CHECK(l.contains(100));
		CHECK(!l.contains(0));
		CHECK(l.length() == 1);
		l = l.tl();
		CHECK(l.isEmpty());
		CHECK(!l.contains(100));
		CHECK(!l.contains(0));
		CHECK(l.length() == 0);
	}

	// test with a garbage collection
	{
		CHECK(l.isEmpty());
		CHECK(l.length() == 0);
		l = gc.cons(100, l);
		CHECK(!l.isEmpty());
		CHECK(l.contains(100));
		CHECK(l.length() == 1);
		l = gc.cons(0, l);
		CHECK(!l.isEmpty());
		CHECK(l.contains(0));
		CHECK(l.contains(100));
		CHECK(l.length() == 2);
		l = l.tl();
		CHECK(!l.isEmpty());
		CHECK(l.contains(100));
		CHECK(!l.contains(0));
		CHECK(l.length() == 1);
		gc.collectGarbage();	// garbage collection
		CHECK(!l.isEmpty());
		CHECK(l.contains(100));
		CHECK(!l.contains(0));
		CHECK(l.length() == 1);
		l = l.tl();
		CHECK(l.isEmpty());
		CHECK(!l.contains(100));
		CHECK(!l.contains(0));
		CHECK(l.length() == 0);
	}

	// robustness test
	{
		MultiplyWithCarryGenerator rand(0xfe003b09);
		bool robust = true;
		for(int i = 0; robust && i < NUM; i++) {

			// perform the action
			t::uint32 r = rand.next();
			t::uint32 action = (r >> 16) % 100;
			if(!lists || action < 20) {
				LOG("creating list " << lists.count());
				lists.add(imm::list<int>::null());
				vecs.add(genstruct::Vector<int>());
			}
			else if(action < 60) {
				int l = ((r >> 8) & 0xff) % lists.count();
				int v = r & 0xff;
				LOG("adding " << v << " to list " << l);
				lists[l] = gc.cons(v, lists[l]);
				vecs[l].push(v);
			}
			else if(action < 90) {
				int l = ((r >> 8) & 0xff) % lists.count();
				int v = r & 0xff;
				if(lists[l]) {
					LOG("removing from list " << l);
					lists[l] = lists[l].tl();
					vecs[l].pop();
				}
			}
			else if(lists.count() > 1) {
				int l = ((r >> 8) & 0xff) % lists.count();
				LOG("deleting list " << (lists.count() - 1));
				lists.pop();
				vecs.pop();
			}

			// check the consistency
			for(int j = 0; j < lists.count(); j++) {
				int k = vecs[j].count() - 1;
				imm::list<int> l = lists[j];
				while(k >= 0 && l && vecs[j][k] == l.hd()) {
					k--;
					l = l.tl();
				}
			}
		}
		CHECK(robust);
	}

TEST_END

