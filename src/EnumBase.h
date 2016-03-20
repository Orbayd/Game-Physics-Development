#ifndef ENUM_BASE
#define ENUM_BASE

struct EnumBase
{
	enum Name
	{
		Stubb // needed for overloading
	};

	bool operator == (EnumBase tmp)
	{
		return (this->value == tmp.value);
	}

	int value;
};

#endif