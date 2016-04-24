struct _FalseType
{
	bool Get()
	{
		return false;
	}
};
struct _TrueType
{
	bool Get()
	{
		return true;
	}
};

template <class _tp>
struct TypeTraits
{
	typedef _FalseType IsPODType;
};

template <>
struct TypeTraits<int>
{
	typedef _TrueType IsPODType;
};