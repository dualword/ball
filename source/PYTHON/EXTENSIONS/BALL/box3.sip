class Box3
{
%TypeHeaderCode
	#include <BALL/MATHS/box3.h>
%End
	public:
	Box3();
	Box3(Box3&);
	Box3(Vector3&, Vector3&, Vector3&, float);
	Box3(Vector3&, Vector3&, Vector3&, Vector3&);

	void set(Box3&);
	float getSurface() const;
	float getVolume() const;
	float getWidth() const;
	float getHeight() const;
	float getDepth() const;
	bool operator == (const Box3&) const;
	bool operator != (Box3&) const;
	bool isValid() const;

	SIP_PYOBJECT __str__();
%MethodCode
	static String tmp;
	tmp = "Box3 { (";
	tmp += String(sipCpp->getWidth()) + " x ";
	tmp += String(sipCpp->getHeight()) + " x ";
	tmp += String(sipCpp->getDepth()) + ") @ ( ";
	tmp += String(sipCpp->getPoint().x) + " ";
	tmp += String(sipCpp->getPoint().y) + " ";
	tmp += String(sipCpp->getPoint().z) + ") }";
	sipRes = PyBytes_FromString(tmp.c_str());
%End
};
