// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//
// $Id: solventDescriptor.C,v 1.10 2004/11/07 19:54:59 oliver Exp $
//

#include <BALL/SOLVATION/solventDescriptor.h>

using namespace std;

namespace BALL
{
	SolventDescriptor::SolventDescriptor()
		:	name_(""),
			number_density_(0),
			solvent_atoms_(),
			valid_(false)
	{
	}

	SolventDescriptor::SolventDescriptor(const SolventDescriptor& solvent)
		:	name_(solvent.name_),
			number_density_(solvent.number_density_),
			solvent_atoms_(solvent.solvent_atoms_),
			valid_(solvent.valid_)
	{
	}

	SolventDescriptor::SolventDescriptor(const String& name, 
			float number_density, 
			const std::vector<SolventAtomDescriptor>& atom_list)
		:	name_(name),
			number_density_(number_density),
			solvent_atoms_(atom_list)
	{
		// ?????: Definieren, wann ein Solvent-Descriptor g�ltig ist.
		valid_ = true;
	}

	void SolventDescriptor::clear()
	{
		name_ = "";
		number_density_ = 0.0;
		solvent_atoms_.clear();
		valid_ = false;
	}

	SolventDescriptor::~SolventDescriptor()
	{
		clear();
		valid_ = false;
	}


	const SolventDescriptor& SolventDescriptor::operator = 
		(const SolventDescriptor& descriptor)
	{
		name_ = descriptor.name_;
		number_density_ = descriptor.number_density_;
		solvent_atoms_ = descriptor.solvent_atoms_;
		valid_ = descriptor.valid_;

		return *this;
	}


	void SolventDescriptor::setName(const String& name)
	{
		name_ = name;
	}


	const String& SolventDescriptor::getName() const
	{
		return name_;
	}


	void SolventDescriptor::setNumberDensity(float number_density)
	{
		number_density_ = number_density;
	}


	float SolventDescriptor::getNumberDensity() const
	{
		return number_density_;
	}


	void SolventDescriptor::setSolventAtomDescriptorList(const
		std::vector<SolventAtomDescriptor>& solvent_atoms)
	{
		solvent_atoms_ = solvent_atoms;
	}


	const std::vector<SolventAtomDescriptor>&
		SolventDescriptor::getSolventAtomDescriptorList() const
	{
		return solvent_atoms_;
	}
	
	std::vector<SolventAtomDescriptor>&
		SolventDescriptor::getSolventAtomDescriptorList()
	{
		return solvent_atoms_;
	}

	Size SolventDescriptor::getNumberOfAtomTypes() const
	{
		return (Size)solvent_atoms_.size();
	}

	const SolventAtomDescriptor& SolventDescriptor::getAtomDescriptor(Position index) const 
	{
		if (index >= solvent_atoms_.size())
		{
			throw(Exception::IndexOverflow(__FILE__, __LINE__, index, (Size)solvent_atoms_.size()));
		}
		
		return solvent_atoms_[index];
	}

	SolventAtomDescriptor& SolventDescriptor::getAtomDescriptor(Position index)  
	{
		if (index >= solvent_atoms_.size())
		{
			throw(Exception::IndexOverflow(__FILE__, __LINE__, index, (Size)solvent_atoms_.size()));
		}
		
		return solvent_atoms_[index];
	}


	bool SolventDescriptor::isValid() const
	{
		return valid_;
	}


	bool SolventDescriptor::operator == (const SolventDescriptor& descriptor) const
	{
		if (solvent_atoms_.size() != descriptor.solvent_atoms_.size())
		{
			// if the solvent descriptions have different sizes, they cannot be equal
			return false;
		}
		
		// go through all elements of the solvent desccription and check equality. 
		// NOTE: This implementation does not recognize descriptions that
		// have the atoms in different order!

		vector<SolventAtomDescriptor>::const_iterator it  =  solvent_atoms_.begin();
		vector<SolventAtomDescriptor>::const_iterator it2 = descriptor.solvent_atoms_.begin();

		for (; it != solvent_atoms_.end(); ++it, ++it2)
		{
			if  ((it->type != it2->type) 
				|| (it->element_symbol != it2->element_symbol)
				|| (it->radius != it2->radius)
				|| (it->number_of_atoms != it2->number_of_atoms))
			{
				return false;
			}
		}

		return true;
	}

}
