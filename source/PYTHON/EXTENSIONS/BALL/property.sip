class NamedProperty
	: PersistentObject
{
%TypeHeaderCode
	#include <BALL/CONCEPT/property.h>
%End
	public:
	NamedProperty(String&);
	NamedProperty(String&, bool);
	NamedProperty(String&, String&);
	NamedProperty(String&, PersistentObject&);
	NamedProperty(NamedProperty&);
	~NamedProperty();
	int getType() const;
	String getName() const;
	bool getBool() const;
	int getInt() const;
	float getFloat() const;
	int getUnsignedInt() const;
	PersistentObject* getObject() const;
	String getString() const;
	NamedProperty();

	SIP_PYOBJECT __str__();
%MethodCode
	if(sipCpp == 0)
	{
		sipRes = PyBytes_FromString("");
	}
	else
	{
		BALL::String output = sipCpp->getName() + ", Type: ";
		switch(sipCpp->getType())
		{
			case NamedProperty::BOOL:
				output += BALL::String("Bool, Value: ") + (sipCpp->getBool() ? "True" : "False");
				break;
			case NamedProperty::INT:
				output += BALL::String("Integer, Value: ") + BALL::String(sipCpp->getInt());
				break;
			case NamedProperty::UNSIGNED_INT:
				output += BALL::String("Unsigned Integer, Value: ") + BALL::String(sipCpp->getUnsignedInt());
				break;
			case NamedProperty::FLOAT:
				output += BALL::String("Float, Value: ") + BALL::String(sipCpp->getFloat());
				break;
			case NamedProperty::DOUBLE:
				output += BALL::String("Double, Value: ") + BALL::String(sipCpp->getDouble());
				break;
			case NamedProperty::STRING:
				output += BALL::String("String, Value: ") + BALL::String(sipCpp->getString());
				break;
			case NamedProperty::OBJECT:
				output += BALL::String("Object, Value: ") + BALL::String((unsigned long) sipCpp->getObject());
				break;
			case NamedProperty::NONE:
				output += BALL::String("None");
				break;
			case NamedProperty::SMART_OBJECT:
				output += BALL::String("Smart Object, Value: ") + BALL::String((unsigned long) &*sipCpp->getSmartObject());
				break;
		}
		sipRes = PyBytes_FromString(output.c_str());
	}
%End
};

class PropertyManager
{
	public:
	PropertyManager();
	PropertyManager(const PropertyManager&);
	~PropertyManager();
  void clear();
	void destroy();
	void set(const PropertyManager&);
	void get(PropertyManager&) const;
	void swap(PropertyManager&);
	void setProperty(int);
	void clearProperty(int);
	void toggleProperty(int);
	int countProperties() const;
	void setProperty(NamedProperty&);
	void setProperty(const String&);
	void setProperty(const String&, float);
	void setProperty(const String&, String&);
	void setProperty(const String&, PersistentObject&);
	const NamedProperty& getProperty(const String&) const;
	void clearProperty(const String&);
	Size countNamedProperties() const;
	NamedProperty& getNamedProperty(Position) throw(IndexOverflow);
	bool hasProperty(int) const;
	bool hasProperty(const String&) const;
	bool isValid() const;
};
