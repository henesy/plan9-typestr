# typestr -- a hidden Plan 9 gem

Excerpts from 9fans describing an undocumented feature Ken added to the Plan 9 C compilers shortly before he left:

[Original](https://groups.google.com/forum/#!msg/comp.os.plan9/uMF7A4gkJsw/kNWBQ8U93LcJ)

	/sys/src/cmd/cc/funct.c gives a further glimmer of illumination.

and

Typestr was one of the things to come out of Ken's parting
flurry of activity. Here's the complete documentation:

	#include <u.h>
	#include <libc.h>
	
	typestr struct _cmplx Cmplx;
	struct _cmplx
	{
		double r;
		double i;
	};
	
	int Zconv(va_list*, Fconv*);
	#pragma varargck type "Z" Cmplx
	
	void
	main(void)
	{
		Cmplx a, b;
		int ia[10];
		double d;
		fmtinstall('Z', Zconv);
		a = (Cmplx){1, 0};
		b = (Cmplx){0, 1};
		a = -((a + b) - (b - a)) + -((a - b) - (b + a));
		print("a = %Z\n", a);
		a += b;
		print("a = %Z\n", a);
		if(a == a)
		print("ok\n");
		a = (d = a);
		print("d = %g\n", d);
		print("a = %Z\n", a);
		a = (Cmplx)1.0;
		print("a = %Z\n", a);
	}
	
	/*
	* print conversion
	*/
	int
	Zconv(va_list *arg, Fconv *fp)
	{
		char s[50];
		Cmplx z;
		z = va_arg(*arg, Cmplx);
		sprint(s, "(%g %g)", z.r, z.i);
		strconv(s, fp);
		return sizeof(z);
	}
	
	/*
	* operators
	*/
	Cmplx
	_cmplx_pos_(Cmplx a)
	{
		Cmplx r;
		r.r = +a.r;
		r.i = +a.i;
		return r;
	}
	
	Cmplx
	_cmplx_neg_(Cmplx a)
	{
		Cmplx r;
		r.r = -a.r;
		r.i = -a.i;
		return r;
	}
	
	Cmplx
	_cmplx_add_(Cmplx a, Cmplx b)
	{
		Cmplx r;
		r.r = a.r + b.r;
		r.i = a.i + b.i;
		return r;
	}
	
	Cmplx
	_cmplx_sub_(Cmplx a, Cmplx b)
	{
		Cmplx r;
		r.r = a.r - b.r;
		r.i = a.i - b.i;
		return r;
	}
	
	int
	_cmplx_eq_(Cmplx a, Cmplx b)
	{
		Cmplx r;
		return a.r == b.r && a.i == b.i;
	}
	
	/*
	* assignment-op (can be made from assig and op)
	*/
	Cmplx
	_cmplx_asadd_(Cmplx *a, Cmplx b)
	{
		*a = *a + b;
		return *a;
	}
	
	Cmplx
	_cmplx_assub_(Cmplx *a, Cmplx b)
	{
		*a = *a - b;
		return *a;
	}
	
	/*
	* conversions
	*/
	int
	_cmplx_i_(Cmplx a)
	{
		return sqrt(a.r*a.r + a.i*a.i);
	}
	
	double
	_cmplx_d_(Cmplx a)
	{
		return sqrt(a.r*a.r + a.i*a.i);
	}
	
	Cmplx
	_d_cmplx_(double a)
	{
		Cmplx r;
		r.r = a;
		r.i = 0;
		return r;
	}

From IRC:

	<aap> didn't ken actually implement some sort of OOP in plan 9 C?
	<mveety> because it does the weird ass smalltalk object model
	<aap> qrstuv played with this i think
	<mveety> aap: what do you mean?
	<henesy> mveety, does obj-c typically compile down to c then asm? or just obj-c -> asm?
	<aap> i forget what the feature was called...typeclass?
	<ndeuteron> typestr?
	<aap> maybe that
	<mveety> henesy: the early compilers did that
	<mveety> i've never heard of the plan9 c object oriented shit
	<aap> qrstuv: you know something about this, right?
	<Ori_B> mveety: the closest is struct embedding, as far as I know.
	<Ori_B> aap: is that what you're talking about?
	<aap> no, it was more
	<Ori_B> hm. no idea then.
	<aap> something like overloading operators iirc?
	<aap> shit, i forget
	<Ori_B> aap: oh.
	<Ori_B> yeah, that's typestr.
	<mveety> the anon members of structs is kinda oo
	<Ori_B> it's in there.
	<mveety> like the struct { QLock; int shit; }; stuff
	<mveety> what typestr?
	<Ori_B> mveety: something like "typestr Bigint foo;; Bigint foo_add(Bigint a, Bigint b) { ... }"
	<Ori_B> and you can use the '+' operator on bigints
	<Ori_B> I'm probably getting the syntax horribly wrong.
	<Ori_B> but that's the general idea.
	<mveety> oh fuck i need that in my life
	<mveety> is this in the compiler paper?
	<Ori_B> I don't think it's documented.
	<Ori_B> I think it was the last thing ken did before leaving bell labs.
	<Ori_B> there's just an email on 9fans, AFAIK
	<mveety> http://comp.os.plan9.narkive.com/J6OjU7wO/9fans-kenc-operator-overloading
