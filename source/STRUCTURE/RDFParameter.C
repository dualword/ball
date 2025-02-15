// -*- Mode: C++; tab-width: 2; -*-
// vi: set ts=2:
//

#include <BALL/STRUCTURE/RDFParameter.h>
#include <BALL/STRUCTURE/RDFSection.h>
#include <BALL/MOLMEC/PARAMETER/forceFieldParameters.h>

using namespace std;

namespace BALL
{

	RDFParameter::RDFParameter() 
		:	ParameterSection(),
			rdf_list_(),
			rdf_indices_()
	{
	}


	RDFParameter::RDFParameter(const RDFParameter& rdf_parameter) 
		:	ParameterSection(rdf_parameter),
			rdf_list_(rdf_parameter.rdf_list_),
			rdf_indices_(rdf_parameter.rdf_indices_)
	{
	}


	RDFParameter::~RDFParameter() 
	{
		clear();
		valid_ = false;
	}


	const RDFParameter& RDFParameter::operator = (const RDFParameter& parameter) 
		
	{
		ParameterSection::operator = (parameter);
		rdf_list_ = parameter.rdf_list_;
		rdf_indices_ = parameter.rdf_indices_;

		return *this;
	}


	void RDFParameter::clear() 
	{
		ParameterSection::clear();
		rdf_list_.clear();
		rdf_indices_.clear();
		valid_ = false;
	}


	bool RDFParameter::hasRDF(Atom::Type solvent_atom_type,
			Atom::Type solute_atom_type) const 
	{
		if (rdf_indices_.has(solvent_atom_type))
		{
			return rdf_indices_[solvent_atom_type].has(solute_atom_type);
		}
		else 
		{
			return false;
		}
	}


	bool RDFParameter::hasParameters(Atom::Type solvent_atom_type,
			Atom::Type solute_atom_type) const 
	{
		return hasRDF(solvent_atom_type, solute_atom_type);
	}
	

	Position RDFParameter::getIndex(Atom::Type type_i, Atom::Type type_j)
		const 
	{
		if (hasRDF(type_i, type_j))
		{
			return rdf_indices_[type_i][type_j];
		}
		else 
		{
			return INVALID_Position;
		}
	}


	const RadialDistributionFunction& RDFParameter::getRDF(Position index)
		const 
	{
		if (index < rdf_list_.size())
		{
			return rdf_list_[index];
		}
		else
		{
			Log.error() << "RDFParameter::getRDF(): "
									<< "Index out of range." <<endl;
			return RTTI::getDefault<RadialDistributionFunction>();
		}
	}


	const RadialDistributionFunction& RDFParameter::getRDF(Atom::Type type_i,
			Atom::Type type_j) const 
	{
		if (hasRDF(type_i, type_j))
		{
			Position index = getIndex(type_i, type_j);
			if (index != INVALID_Position)
			{
				return getRDF(index);
			}
			else
			{
				Log.error() << "RDFParameter::getRDF(): "
										<< "RDf for type combination  (" << type_i << "," << type_j 
										<< ") could not be found." << endl 
										<< "Something went terribly wrong." << endl;
				return RTTI::getDefault<RadialDistributionFunction>();
			}
		}
		else
		{
			Log.error() << "RDFParameter::getRDF(): "
									<< "no RDf defined for type combination  (" << type_i << "," 
									<< type_j << ")" << endl;
			return RTTI::getDefault<RadialDistributionFunction>();
		}
	}


	bool RDFParameter::extractSection(ForceFieldParameters& parameters,
			const String& section_name) 
	{

		if (!parameters.isValid())
		{
			return false;
		}

		// first clear the instance, just in case there is something left from
		// before

		clear();

		ParameterSection::extractSection(parameters, section_name);

		Size index_name = getColumnIndex("name");
		String key;
		String type_name_i;
		String type_name_j;
		Atom::Type type_i;
		Atom::Type type_j;
		Size number_of_keys = getNumberOfKeys();
		AtomTypes& atom_types = parameters.getAtomTypes();         

		for (Size i = 0; i < number_of_keys; ++i)
		{
			key = getKey(i);
			if ((key.size() > 0) && (key.find_first_of(" ", 0) > 0)) 
			{
				type_name_i = key.before(" ", 0);
				type_name_j = key.after(" ", 0); 
				/*
				Log.info() << "About to read RDF for combination " << type_name_i 
					<< " " << type_name_j << endl;
				*/
				if ((atom_types.hasType(type_name_i)) && 
						(atom_types.hasType(type_name_j)))
				{
					type_i = atom_types.getType(type_name_i);
					type_j = atom_types.getType(type_name_j);
					String name_ij = getValue(i, index_name);

					HashMap<Atom::Type, HashMap<Atom::Type, Position> >::Iterator it;

					RDFSection rdf_section;

					if (rdf_section.extractSection(parameters, name_ij))
					{
						rdf_list_.push_back(rdf_section.getRDF());
						Position index = (Position)rdf_list_.size() - 1;

						if (rdf_indices_.has(type_i))
						{
							it = rdf_indices_.find(type_i);
							if (it->second.has(type_j))
							{
								Log.error() << "RDFParameter::extractSection(): "
														<< "Trying to overwrite existing definition." << endl;
								return false;
							}
							else
							{
								// Hier wird der Typ klar.
								it->second.insert(std::pair<Atom::Type, Position>(type_j, index));
							}
						}
						else
						{
							HashMap<Atom::Type, Position> tmp;
							tmp[type_j] = index;
							rdf_indices_.insert(std::pair<Atom::Type,
							HashMap<Atom::Type, Position> >(type_i, tmp));
						}
					}
					else
					{
						Log.error() << "RDFParameter::extractSection(): "
												<< "Cannot read RDF section" << endl;
						return false;
					}
				}
				else
				{
					Log.error() << "RDFParameter::extractSection(): "
											<< "cannot assign atom types."<< endl;
					return false;
				}
			}
		}
		return true;
	}

}
