// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/CONCEPT/classTest.h>
#include <BALLTestConfig.h>

///////////////////////////
#include <BALL/KERNEL/nucleotide.h>
#include <BALL/KERNEL/nucleicAcid.h>
#include <BALL/KERNEL/atom.h>
#include <BALL/CONCEPT/textPersistenceManager.h>
#include <BALL/KERNEL/PTE.h>
///////////////////////////

START_TEST(Nucleotide)

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

using namespace BALL;
using namespace std;

String filename;
NEW_TMP_FILE(filename)

Nucleotide*	n;
CHECK(Nucleotide() throw())
	n = new Nucleotide;
	TEST_NOT_EQUAL(n, 0)
RESULT

CHECK(~Nucleotide() throw())
	delete n;
RESULT

CHECK(Nucleotide(const Nucleotide& nucleotide, bool deep = true) throw())
	Nucleotide* n1 = new Nucleotide;
	n1->setName("testname");
	Atom a(PTE[Element::HELIUM],"a");
	n1->insert(a);
	Nucleotide* n2 = new Nucleotide(*n1, true);
	TEST_NOT_EQUAL(n2, 0)
	if (n2 != 0)
	{
		TEST_EQUAL(n2->getName(), "testname")
		TEST_EQUAL(n2->getAtom(0)->getName(), "a")
		delete n2;
	}
	n2 = new Nucleotide(*n1, false);
	TEST_NOT_EQUAL(n2, 0)
	if (n2 != 0)
	{
		TEST_EQUAL(n2->getName(), "testname")
		delete n2;
	}
	delete n1;
RESULT

CHECK(Nucleotide(const String& name, const String& id = BALL_NUCLEOTIDE_DEFAULT_ID, char insertion_code = BALL_NUCLEOTIDE_DEFAULT_INSERTION_CODE) throw())
	Nucleotide* n1 = new Nucleotide("n1", "id", 'i');
	TEST_NOT_EQUAL(n1, 0)
	if (n1 != 0)
	{
		TEST_EQUAL(n1->getName(), "n1")
		TEST_EQUAL(n1->getID(), "id")
		TEST_EQUAL(n1->getInsertionCode(), 'i')
		delete n1;
	}
	Nucleotide* n2 = new Nucleotide("n1");
	TEST_NOT_EQUAL(n2, 0)
	if (n2 != 0)
	{
		TEST_EQUAL(n2->getName(), "n1")
		TEST_EQUAL(n2->getID(), "")
		TEST_EQUAL(n2->getInsertionCode(), ' ')
		delete n2;
	}
RESULT

CHECK(void clear() throw())
	Nucleotide n("n1", "id", 'c');
	Atom a(PTE[Element::HELIUM],"a");
	n.insert(a);
	NucleicAcid c;
	c.insert(n);
	n.clear();
	TEST_EQUAL(n.countAtoms(), 0)
	TEST_EQUAL(n.getID(), "")
	TEST_EQUAL(n.getInsertionCode(), ' ')
	TEST_EQUAL(c.getNucleotide(0), &n)
RESULT

CHECK(void destroy() throw())
	Nucleotide n("n1", "id", 'c');
	Atom a(PTE[Element::HELIUM],"a");
	n.insert(a);
	NucleicAcid c;
	c.insert(n);
	n.destroy();
	TEST_EQUAL(n.countAtoms(), 0)
	TEST_EQUAL(n.getID(), "")
	TEST_EQUAL(n.getInsertionCode(), ' ')
	TEST_EQUAL(c.getNucleotide(0), 0)
RESULT

CHECK(void set(const Nucleotide& nucleotide, bool deep = true) throw())
	Nucleotide n1("n1");
	Atom a(PTE[Element::HELIUM],"a");
	n1.insert(a);
	Nucleotide n2("n2");
	n2.set(n1, false);
	TEST_EQUAL(n2.getName(), "n1")
	TEST_EQUAL(n2.countAtoms(), 0)
	n2.setName("a");
	n2.set(n1);
	TEST_EQUAL(n2.getName(), "n1")
	TEST_EQUAL(n2.countAtoms(), 1)
RESULT

CHECK(Nucleotide& operator = (const Nucleotide& nucleotide) throw())
	Nucleotide n1("n1");
	Atom a(PTE[Element::HELIUM],"a");
	n1.insert(a);
	Nucleotide n2("n2");
	n2 = n1;
	TEST_EQUAL(n2.getName(), "n1")
	TEST_EQUAL(n2.countAtoms(), 1)
RESULT

CHECK(void get(Nucleotide& nucleotide, bool deep = true) const throw())
	Nucleotide n1("n1");
	Atom a(PTE[Element::HELIUM],"a");
	n1.insert(a);
	Nucleotide n2("n2");
	n1.get(n2, false);
	TEST_EQUAL(n2.getName(), "n1")
	TEST_EQUAL(n2.countAtoms(), 0)
	n2.setName("a");
	n1.get(n2);
	TEST_EQUAL(n2.getName(), "n1")
	TEST_EQUAL(n2.countAtoms(), 1)
RESULT

CHECK(void swap(Nucleotide& nucleotide) throw())
	Nucleotide n1("n1");
	Nucleotide n2("n2");
	Atom a1(PTE[Element::HELIUM],"a");
	Atom a2(PTE[Element::HELIUM],"a");
	n1.insert(a1);
	n2.insert(a2);
	n1.swap(n2);
	TEST_EQUAL(n1.getName(), "n2")
	TEST_EQUAL(n1.getAtom(0), &a2)
	TEST_EQUAL(n2.getName(), "n1")
	TEST_EQUAL(n2.getAtom(0), &a1)
RESULT

CHECK(NucleicAcid* getNucleicAcid() throw())
	Nucleotide n1("n1");
	TEST_EQUAL(n1.getNucleicAcid(), 0)
	NucleicAcid c;
	c.insert(n1);
	n1.getNucleicAcid()->setName("c");
	TEST_EQUAL(c.getName(), "c")
RESULT

CHECK(const NucleicAcid* getNucleicAcid() const throw())
	Nucleotide n1("n1");
	NucleicAcid c;
	c.insert(n1);
	TEST_EQUAL(n1.getNucleicAcid(), &c)
RESULT

CHECK([EXTRA]Nucleotide::getAtom(Position position))
	Nucleotide n1("n1");
	TEST_EQUAL(n1.getAtom(0), 0)
	Atom a1(PTE[Element::HELIUM],"a");
	n1.insert(a1);
	n1.getAtom(0)->setName("a1");
	TEST_EQUAL(a1.getName(), "a1")
RESULT

CHECK([EXTRA]Nucleotide::getAtom(Position position) const )
	Nucleotide n1("n1");
	TEST_EQUAL(n1.getAtom(0), 0)
	Atom a1(PTE[Element::HELIUM],"a1");
	n1.insert(a1);
	TEST_EQUAL(n1.getAtom(0), &a1)
RESULT

CHECK(void setID(const String& id) throw())
	Nucleotide n1("x");
	TEST_EQUAL(n1.getID(), "")
	n1.setID("");
	TEST_EQUAL(n1.getID(), "")
	n1.setID("n1");
	TEST_EQUAL(n1.getID(), "n1")
RESULT

CHECK(const String& getID() const throw())
	Nucleotide n1("x");
	TEST_EQUAL(n1.getID(), "")
	n1.setID("");
	TEST_EQUAL(n1.getID(), "")
	n1.setID("n1");
	TEST_EQUAL(n1.getID(), "n1")
RESULT

CHECK(void setInsertionCode(char insertion_code) throw())
	Nucleotide n1('x');
	TEST_EQUAL(n1.getInsertionCode(), ' ')
	n1.setInsertionCode('r');
	TEST_EQUAL(n1.getInsertionCode(), 'r')
RESULT

CHECK(setInsertionCode invalid)
	Nucleotide n1('x');

	TEST_EQUAL(n1.getInsertionCode(), ' ');
	TEST_EXCEPTION(Exception::InvalidArgument, n1.setInsertionCode('\0'));
	TEST_EQUAL(n1.getInsertionCode(), ' ');
RESULT

CHECK(void unsetInsertionCode())
	Nucleotide n1('x');

	TEST_EQUAL(n1.getInsertionCode(), ' ');
	n1.setInsertionCode('A');
	TEST_EQUAL(n1.getInsertionCode(), 'A');
	n1.unsetInsertionCode();
	TEST_EQUAL(n1.getInsertionCode(), ' ');
RESULT


CHECK(char getInsertionCode() const throw())
	Nucleotide n1('x');
	TEST_EQUAL(n1.getInsertionCode(), ' ')
	n1.setInsertionCode('r');
	TEST_EQUAL(n1.getInsertionCode(), 'r')
RESULT

CHECK([EXTRA]Nucleotide::countAtoms() const )
	Nucleotide n1('x');
	Atom a(PTE[Element::HELIUM],"a");
	TEST_EQUAL(n1.countAtoms(), 0)
	n1.insert(a);
	TEST_EQUAL(n1.countAtoms(), 1)
RESULT

CHECK([EXTRA]Nucleotide::prepend(Atom& atom))
	Nucleotide n1('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	n1.prepend(a1);
	n1.prepend(a2);
	TEST_EQUAL(n1.getAtom(0), &a2)
	TEST_EQUAL(n1.getAtom(1), &a1)
RESULT

CHECK([EXTRA]Nucleotide::append(Atom& atom))
	Nucleotide n1('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	n1.append(a1);
	n1.append(a2);
	TEST_EQUAL(n1.getAtom(0), &a1)
	TEST_EQUAL(n1.getAtom(1), &a2)
RESULT

CHECK([EXTRA]Nucleotide::insert(Atom& atom))
	Nucleotide n1('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	n1.insert(a1);
	n1.insert(a2);
	TEST_EQUAL(n1.getAtom(0), &a1)
	TEST_EQUAL(n1.getAtom(1), &a2)
RESULT

CHECK([EXTRA]Nucleotide::insertBefore(Atom& atom, Composite& before))
	Nucleotide n1('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	Atom a3(PTE[Element::HELIUM],"a3");
	n1.insert(a1);
	n1.insert(a2);
	n1.insertBefore(a3, a2);
	TEST_EQUAL(n1.getAtom(0), &a1)
	TEST_EQUAL(n1.getAtom(1), &a3)
	TEST_EQUAL(n1.getAtom(2), &a2)
RESULT

CHECK([EXTRA]Nucleotide::insertAfter(Atom& atom, Composite& after))
	Nucleotide n1('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	Atom a3(PTE[Element::HELIUM],"a3");
	n1.insert(a1);
	n1.insert(a2);
	n1.insertAfter(a3, a2);
	TEST_EQUAL(n1.getAtom(0), &a1)
	TEST_EQUAL(n1.getAtom(1), &a2)
	TEST_EQUAL(n1.getAtom(2), &a3)
RESULT

CHECK([EXTRA]Nucleotide::remove(Atom& atom))
	Nucleotide n1('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	Atom a3(PTE[Element::HELIUM],"a3");
	n1.insert(a1);
	n1.insert(a2);
	n1.insertAfter(a3, a2);
	n1.remove(a2);
	TEST_EQUAL(n1.getAtom(0), &a1)
	TEST_EQUAL(n1.getAtom(1), &a3)
RESULT

CHECK(void spliceBefore(Nucleotide& nucleotide) throw())
	Nucleotide n1('x');
	Nucleotide n2('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	n1.insert(a1);
	n2.insert(a2);
	n1.spliceBefore(n2);
	TEST_EQUAL(n1.getAtom(0), &a2)
	TEST_EQUAL(n1.getAtom(1), &a1)
RESULT

CHECK(void spliceAfter(Nucleotide& nucleotide) throw())
	Nucleotide n1('x');
	Nucleotide n2('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	n1.insert(a1);
	n2.insert(a2);
	n1.spliceAfter(n2);
	TEST_EQUAL(n1.getAtom(0), &a1)
	TEST_EQUAL(n1.getAtom(1), &a2)
RESULT

CHECK(void splice(Nucleotide& nucleotide) throw())
	Nucleotide n1('x');
	Nucleotide n2('x');
	Atom a1(PTE[Element::HELIUM],"a1");
	Atom a2(PTE[Element::HELIUM],"a2");
	n1.insert(a1);
	n2.insert(a2);
	n1.splice(n2);
	TEST_EQUAL(n1.getAtom(0), &a2)
	TEST_EQUAL(n1.getAtom(1), &a1)
RESULT

CHECK(bool isTerminal() const throw())
	Nucleotide n1('x');
	TEST_EQUAL(n1.isTerminal(), false)
	NucleicAcid c1;
	c1.insert(n1);
	TEST_EQUAL(n1.isTerminal(), true)
	Nucleotide n2('x');
	Nucleotide n3('x');
	c1.append(n2);
	TEST_EQUAL(n1.isTerminal(), true)
	c1.prepend(n3);
	TEST_EQUAL(n1.isTerminal(), false)
RESULT

CHECK(bool is3Prime() const throw())
	Nucleotide n1('x');
	TEST_EQUAL(n1.is3Prime(), false)
	NucleicAcid c1;
	c1.insert(n1);
	TEST_EQUAL(n1.is3Prime(), true)
	Nucleotide n2('x');
	Nucleotide n3('x');
	c1.append(n2);
	TEST_EQUAL(n1.is3Prime(), true)
	c1.prepend(n3);
	TEST_EQUAL(n1.is3Prime(), false)
RESULT

CHECK(bool is5Prime() const throw())
	Nucleotide n1('x');
	TEST_EQUAL(n1.is5Prime(), false)
	NucleicAcid c1;
	c1.insert(n1);
	TEST_EQUAL(n1.is5Prime(), true)
	Nucleotide n2('x');
	Nucleotide n3('x');
	c1.prepend(n3);
	TEST_EQUAL(n1.is5Prime(), true)
	c1.append(n2);
	TEST_EQUAL(n1.is5Prime(), false)
RESULT

CHECK(bool isValid() const throw())
	Nucleotide n("n1", "id", 'i');
	TEST_EQUAL(n.isValid(), true)
	n.setName("");
	TEST_EQUAL(n.isValid(), true)
RESULT

CHECK(void dump(std::ostream& s = std::cout, Size depth = 0) const throw())
	Nucleotide n1("n1", "test", 'X');
	Atom a1(PTE[Element::HELIUM],"a1");
	n1.insert(a1);
	std::ofstream outfile(filename.c_str(), std::ios::out);
	n1.dump(outfile);
	outfile.close();
	TEST_FILE_REGEXP(filename.c_str(), BALL_TEST_DATA_PATH(Nucleotide_test.txt))
RESULT

TextPersistenceManager pm;
using namespace RTTI;
pm.registerClass(getStreamName<Nucleotide>(), Nucleotide::createDefault);
pm.registerClass(getStreamName<Atom>(), Atom::createDefault);
NEW_TMP_FILE(filename)
CHECK(void persistentWrite(PersistenceManager& pm, const char* name = 0) const)
	std::ofstream	ofile(filename.c_str(), std::ios::out);
	Nucleotide* f1= new Nucleotide("name1");
	Atom* f2 = new Atom();
	f2->setName("name2");
	f1->insert(*f2);
	Atom* f3 = new Atom();
	f3->setName("name3");
	f1->insert(*f3);
	pm.setOstream(ofile);
	*f1 >> pm;
	ofile.close();
	delete f1;
RESULT

CHECK(void persistentRead(PersistenceManager& pm))
	std::ifstream	ifile(filename.c_str());
	pm.setIstream(ifile);
	PersistentObject*	ptr = pm.readObject();
	TEST_NOT_EQUAL(ptr, 0)
	if (ptr != 0)
	{
        TEST_EQUAL(isKindOf<Nucleotide>(ptr), true)
		Nucleotide*	f1 = castTo<Nucleotide>(*ptr);
		TEST_EQUAL(f1->getName(), "name1")
		TEST_EQUAL(f1->countAtoms(), 2)
		TEST_EQUAL(f1->getAtom(0)->getName(), "name2")
		TEST_EQUAL(f1->getAtom(1)->getName(), "name3")
		delete f1;
	} 
	else 
	{
		throw Exception::NullPointer(__FILE__, __LINE__);
	}
RESULT

CHECK(bool operator == (const Nucleotide& nucleotide) const throw())
	Nucleotide b1;
	Nucleotide b2;
	TEST_EQUAL(b1 == b2, false)
	b1 = b2;
	TEST_EQUAL(b1 == b1, true)
RESULT

CHECK(bool operator != (const Nucleotide& nucleotide) const throw())
	Nucleotide b1;
	Nucleotide b2;
	TEST_EQUAL(b1 != b2, true)
	b1 = b2;
	TEST_EQUAL(b1 != b1, false)
RESULT

CHECK(BALL_CREATE_DEEP(Nucleotide))
	Nucleotide n1("n1", "test", 'X');
	Atom a1(PTE[Element::HELIUM],"a1");
	n1.insert(a1);
	Nucleotide* n = (Nucleotide*) n1.create(false, true);
	TEST_EQUAL(n->getName(), "")
	TEST_EQUAL(n->getID(), BALL_NUCLEOTIDE_DEFAULT_ID)
	TEST_EQUAL(n->getInsertionCode(), BALL_NUCLEOTIDE_DEFAULT_INSERTION_CODE)
	TEST_EQUAL(n->countAtoms(), 0)
	delete n;
	n = (Nucleotide*) n1.create(true, false);
	TEST_EQUAL(n->getName(), "n1")
	TEST_EQUAL(n->getID(), "test")
	TEST_EQUAL(n->getInsertionCode(), 'X')
	TEST_EQUAL(n->countAtoms(), 1)
	TEST_EQUAL(n->getAtom(0)->getName(), "a1")
	delete n;
RESULT


CHECK(void prepend(Atom& atom) throw())
	Nucleotide ac1;
	Atom a1;
	Atom a2;
	ac1.insert(a1);
	TEST_EQUAL(ac1.getAtom(0), &a1)
	ac1.prepend(a2);
	TEST_EQUAL(ac1.getAtom(0), &a2)
	TEST_EQUAL(ac1.getAtom(1), &a1)
RESULT

CHECK(void insert(Atom& atom) throw())
	Nucleotide ac1;
	Atom a1;
	Atom a2;
	ac1.insert(a1);
	TEST_EQUAL(ac1.getAtom(0), &a1)
	ac1.insert(a2);
	TEST_EQUAL(ac1.getAtom(0), &a1)
	TEST_EQUAL(ac1.getAtom(1), &a2)
RESULT

CHECK(void append(Atom& atom) throw())
	Nucleotide ac1;
	Atom a1;
	Atom a2;
	ac1.insert(a1);
	ac1.append(a2);
	TEST_EQUAL(ac1.getAtom(0), &a1)
	TEST_EQUAL(ac1.getAtom(1), &a2)
RESULT

CHECK(void insertBefore(Atom& atom, Composite& before) throw())
	Nucleotide ac1;
	Atom a1;
	Atom a2;
	Atom a3;
	ac1.insert(a1);
	ac1.append(a2);
	ac1.insertBefore(a3, a2);
	TEST_EQUAL(ac1.getAtom(0), &a1)
	TEST_EQUAL(ac1.getAtom(1), &a3)
	TEST_EQUAL(ac1.getAtom(2), &a2)
RESULT

CHECK(void insertAfter(Atom& atom, Composite& after) throw())
	Nucleotide ac1;
	Atom a1;
	Atom a2;
	Atom a3;
	ac1.insert(a1);
	ac1.append(a2);
	ac1.insertAfter(a3, a1);
	TEST_EQUAL(ac1.getAtom(0), &a1)
	TEST_EQUAL(ac1.getAtom(1), &a3)
	TEST_EQUAL(ac1.getAtom(2), &a2)
RESULT

CHECK(bool remove(Atom& atom) throw())
	Nucleotide ac1;
	Atom a;
	ac1.insert(a);
	ac1.remove(a);
	TEST_EQUAL(ac1.getAtom(0), 0)
	ac1.remove(a);
RESULT

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////
END_TEST
