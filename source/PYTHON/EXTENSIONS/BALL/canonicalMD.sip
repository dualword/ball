class CanonicalMD
	: MolecularDynamics
{
%TypeHeaderCode
	#include <BALL/MOLMEC/MDSIMULATION/canonicalMD.h>
%End

	public:
	CanonicalMD();
	CanonicalMD(ForceField&);
	CanonicalMD(ForceField&,SnapShotManager*);
	CanonicalMD(ForceField&,SnapShotManager*, const Options&);
	CanonicalMD(const CanonicalMD&);
	~CanonicalMD() throw();
	void setBathRelaxationTime(double);
	double getBathRelaxationTime() const;
	virtual bool setup(ForceField&, SnapShotManager*) throw();
	virtual bool setup(ForceField&, SnapShotManager*, const Options&) throw();
	virtual bool specificSetup() throw();
	virtual void setTimeStep(double) throw();
	virtual bool simulateIterations(Size, bool restart = false) throw();
};
