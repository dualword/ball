class EnergyMinimizer
{
%TypeHeaderCode
	#include <BALL/MOLMEC/MINIMIZATION/energyMinimizer.h>
%End
	public:

	EnergyMinimizer();
	EnergyMinimizer(ForceField&);
	EnergyMinimizer(ForceField&, Options&);

	bool isValid() const;
	bool setup(ForceField&);
	bool setup(ForceField&, SnapShotManager*);
	bool setup(ForceField&, SnapShotManager*,  Options&);
	bool setup(ForceField&, Options&);
	virtual bool specificSetup();
	virtual bool isConverged() const;
	virtual double findStep();
	virtual void updateDirection();
	virtual double updateEnergy();
	virtual void updateForces();
	virtual void printEnergy() const;
	virtual void takeSnapShot() const;
	virtual void finishIteration();
	int getNumberOfIterations() const;
	Gradient& getDirection();
	Gradient& getGradient();
	Gradient& getInitialGradient();
	double getEnergy() const;
	double getInitialEnergy() const;
	void setNumberOfIterations(int);
	int getMaxNumberOfIterations() const;
	void setMaxNumberOfIterations(int);
	void setMaxSameEnergy(int);
	int getMaxSameEnergy() const;
	void setEnergyOutputFrequency(int);
	int getEnergyOutputFrequency() const;
	void setEnergyDifferenceBound(float);
	float getEnergyDifferenceBound() const;
	void  setMaxGradient(float);
	float getMaxGradient() const;
	void setMaximumDisplacement(float);
	float getMaximumDisplacement() const;
	void setSnapShotFrequency(int);
	int getSnapShotFrequency() const;
	ForceField* getForceField();
	virtual bool minimize(Size = 0, bool = false);
	Options options;
};
