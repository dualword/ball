class Residue
	: Fragment
{
%TypeHeaderCode
	#include <BALL/KERNEL/residue.h>
%End
	public:

	enum Property
	{
		PROPERTY__NON_STANDARD,
		PROPERTY__AMINO_ACID,
		PROPERTY__WATER,
		PROPERTY__HAS_SSBOND,
		PROPERTY__C_TERMINAL,
		PROPERTY__N_TERMINAL,
		PROPERTY__CYCLIC,
		NUMBER_OF_PROPERTIES
	};

	enum FullNameType
	{
		NO_VARIANT_EXTENSIONS,
		ADD_VARIANT_EXTENSIONS
	};

	Residue();
	Residue(const Residue&, bool deep = true);
	Residue(const String&, const String& id = "" , char insertion_code = ' ' );
	~Residue() throw();
	virtual void clear() throw();
	virtual void destroy() throw();
	void set(const Residue&, bool deep = true);
	void get(Residue&, bool deep = true) const;
	void swap(Residue&);
	String getFullName(FullNameType type = ADD_VARIANT_EXTENSIONS) const;
	bool hasTorsionPhi() const;
	Angle getTorsionPhi() const;
	bool hasTorsionPsi() const;
	Angle getTorsionPsi() const;

	Protein* getProtein();
	Chain* getChain();
	PDBAtom* getPDBAtom(Position);
	SecondaryStructure* getSecondaryStructure() throw();

	void setID(const String&);
	const String& getID() const;
	void setInsertionCode(char);
	void unsetInsertionCode();
	char getInsertionCode() const;
	Size countPDBAtoms() const;
	void prepend(PDBAtom& /Transfer/);
	void append(PDBAtom& /Transfer/);
	void insert(PDBAtom& /Transfer/);
	void insertBefore(PDBAtom& /Transfer/, Composite&);
	void insertAfter(PDBAtom& /Transfer/, Composite&);
	bool remove(PDBAtom&);
	void spliceBefore(Residue&);
	void spliceAfter(Residue&);
	void splice(Residue&);
	bool isAminoAcid() const;
	bool isTerminal() const;
	bool isNTerminal() const;
	bool isCTerminal() const;
	virtual bool isValid() const throw();

	SIP_PYOBJECT __str__();
%MethodCode
	sipRes = PyBytes_FromString(String(String("Residue ") + sipCpp->getName() + sipCpp->getID()
		+ " { " + String(sipCpp->countAtoms()) + " atoms }").c_str());
%End
};
