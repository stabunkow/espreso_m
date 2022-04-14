
#include "triangle.h"

using namespace espreso;

bool Triangle::gpw(int order, std::vector<double> &r, std::vector<double> &s, std::vector<double> &w)
{
	switch (order) {
	case 0:
	case 1:
		r.resize(1); s.resize(1); w.resize(1);
		r[ 0] =  0.33333333333333333333333333333333   ;   s[ 0] =  0.33333333333333333333333333333333   ;   w[ 0] =  0.5                                 ;
		break;

	case 2:
		r.resize(3); s.resize(3); w.resize(3);
		r[ 0] =  0.16666666666666666666666666666667   ;   s[ 0] =  0.16666666666666666666666666666667   ;   w[ 0] =  0.16666666666666666666666666666667  ;
		r[ 1] =  0.16666666666666666666666666666667   ;   s[ 1] =  0.66666666666666666666666666666667   ;   w[ 1] =  0.16666666666666666666666666666667  ;
		r[ 2] =  0.66666666666666666666666666666667   ;   s[ 2] =  0.16666666666666666666666666666667   ;   w[ 2] =  0.16666666666666666666666666666667  ;
		break;

	case 3:
		r.resize(4); s.resize(4); w.resize(4);
		r[ 0] =  0.2                                  ;   s[ 0] =  0.2                                  ;   w[ 0] =  0.26041666666666666666666666666667  ;
		r[ 1] =  0.2                                  ;   s[ 1] =  0.6                                  ;   w[ 1] =  0.26041666666666666666666666666667  ;
		r[ 2] =  0.6                                  ;   s[ 2] =  0.2                                  ;   w[ 2] =  0.26041666666666666666666666666667  ;
		r[ 3] =  0.33333333333333333333333333333333   ;   s[ 3] =  0.33333333333333333333333333333333   ;   w[ 3] = -0.28125                             ;
		break;

	case 4:
		r.resize(6); s.resize(6); w.resize(6);
		r[ 0] =  0.091576213509770743459571463402202  ;   s[ 0] =  0.091576213509770743459571463402202  ;   w[ 0] =  0.054975871827660933819163162450105 ;
		r[ 1] =  0.091576213509770743459571463402202  ;   s[ 1] =  0.8168475729804585130808570731956    ;   w[ 1] =  0.054975871827660933819163162450105 ;
		r[ 2] =  0.8168475729804585130808570731956    ;   s[ 2] =  0.091576213509770743459571463402202  ;   w[ 2] =  0.054975871827660933819163162450105 ;
		r[ 3] =  0.44594849091596488631832925388305   ;   s[ 3] =  0.44594849091596488631832925388305   ;   w[ 3] =  0.11169079483900573284750350421656  ;
		r[ 4] =  0.44594849091596488631832925388305   ;   s[ 4] =  0.1081030181680702273633414922339    ;   w[ 4] =  0.11169079483900573284750350421656  ;
		r[ 5] =  0.1081030181680702273633414922339    ;   s[ 5] =  0.44594849091596488631832925388305   ;   w[ 5] =  0.11169079483900573284750350421656  ;
		break;

	case 5:
		r.resize(7); s.resize(7); w.resize(7);
		r[ 0] =  0.47014206410511508977044120951345   ;   s[ 0] =  0.47014206410511508977044120951345   ;   w[ 0] =  0.066197076394253090368824693916576 ;
		r[ 1] =  0.47014206410511508977044120951345   ;   s[ 1] =  0.059715871789769820459117580973105  ;   w[ 1] =  0.066197076394253090368824693916576 ;
		r[ 2] =  0.059715871789769820459117580973105  ;   s[ 2] =  0.47014206410511508977044120951345   ;   w[ 2] =  0.066197076394253090368824693916576 ;
		r[ 3] =  0.10128650732345633880098736191512   ;   s[ 3] =  0.10128650732345633880098736191512   ;   w[ 3] =  0.062969590272413576297841972750091 ;
		r[ 4] =  0.10128650732345633880098736191512   ;   s[ 4] =  0.79742698535308732239802527616975   ;   w[ 4] =  0.062969590272413576297841972750091 ;
		r[ 5] =  0.79742698535308732239802527616975   ;   s[ 5] =  0.10128650732345633880098736191512   ;   w[ 5] =  0.062969590272413576297841972750091 ;
		r[ 6] =  0.33333333333333333333333333333333   ;   s[ 6] =  0.33333333333333333333333333333333   ;   w[ 6] =  0.1125                              ;
		break;

	case 6:
		r.resize(12); s.resize(12); w.resize(12);
		r[ 0] =  0.063089014491502228340331602870819  ;   s[ 0] =  0.063089014491502228340331602870819  ;   w[ 0] =  0.025422453185103408460468404553434 ;
		r[ 1] =  0.063089014491502228340331602870819  ;   s[ 1] =  0.87382197101699554331933679425836   ;   w[ 1] =  0.025422453185103408460468404553434 ;
		r[ 2] =  0.87382197101699554331933679425836   ;   s[ 2] =  0.063089014491502228340331602870819  ;   w[ 2] =  0.025422453185103408460468404553434 ;
		r[ 3] =  0.24928674517091042129163855310702   ;   s[ 3] =  0.24928674517091042129163855310702   ;   w[ 3] =  0.05839313786318968301264480569279  ;
		r[ 4] =  0.24928674517091042129163855310702   ;   s[ 4] =  0.50142650965817915741672289378596   ;   w[ 4] =  0.05839313786318968301264480569279  ;
		r[ 5] =  0.50142650965817915741672289378596   ;   s[ 5] =  0.24928674517091042129163855310702   ;   w[ 5] =  0.05839313786318968301264480569279  ;
		r[ 6] =  0.053145049844816947353249671631402  ;   s[ 6] =  0.31035245103378440541660773395655   ;   w[ 6] =  0.041425537809186787596776728210221 ;
		r[ 7] =  0.31035245103378440541660773395655   ;   s[ 7] =  0.053145049844816947353249671631402  ;   w[ 7] =  0.041425537809186787596776728210221 ;
		r[ 8] =  0.63650249912139864723014259441205   ;   s[ 8] =  0.053145049844816947353249671631402  ;   w[ 8] =  0.041425537809186787596776728210221 ;
		r[ 9] =  0.63650249912139864723014259441205   ;   s[ 9] =  0.31035245103378440541660773395655   ;   w[ 9] =  0.041425537809186787596776728210221 ;
		r[10] =  0.053145049844816947353249671631402  ;   s[10] =  0.63650249912139864723014259441205   ;   w[10] =  0.041425537809186787596776728210221 ;
		r[11] =  0.31035245103378440541660773395655   ;   s[11] =  0.63650249912139864723014259441205   ;   w[11] =  0.041425537809186787596776728210221 ;
		break;

	case 7:
		r.resize(13); s.resize(13); w.resize(13);
		r[ 0] =  0.065130102902215811538025906311975  ;   s[ 0] =  0.065130102902215811538025906311975  ;   w[ 0] =  0.026673617804419245634993644449534 ;
		r[ 1] =  0.065130102902215811538025906311975  ;   s[ 1] =  0.86973979419556837692394818737605   ;   w[ 1] =  0.026673617804419245634993644449534 ;
		r[ 2] =  0.86973979419556837692394818737605   ;   s[ 2] =  0.065130102902215811538025906311975  ;   w[ 2] =  0.026673617804419245634993644449534 ;
		r[ 3] =  0.63844418856980972680033396470319   ;   s[ 3] =  0.048690315425316411793021558528414  ;   w[ 3] =  0.038556880445128570129932596275576 ;
		r[ 4] =  0.63844418856980972680033396470319   ;   s[ 4] =  0.3128654960048738614066444767684    ;   w[ 4] =  0.038556880445128570129932596275576 ;
		r[ 5] =  0.048690315425316411793021558528414  ;   s[ 5] =  0.63844418856980972680033396470319   ;   w[ 5] =  0.038556880445128570129932596275576 ;
		r[ 6] =  0.048690315425316411793021558528414  ;   s[ 6] =  0.3128654960048738614066444767684    ;   w[ 6] =  0.038556880445128570129932596275576 ;
		r[ 7] =  0.3128654960048738614066444767684    ;   s[ 7] =  0.63844418856980972680033396470319   ;   w[ 7] =  0.038556880445128570129932596275576 ;
		r[ 8] =  0.3128654960048738614066444767684    ;   s[ 8] =  0.048690315425316411793021558528414  ;   w[ 8] =  0.038556880445128570129932596275576 ;
		r[ 9] =  0.26034596607903982692624246913924   ;   s[ 9] =  0.26034596607903982692624246913924   ;   w[ 9] =  0.087807628716603905876759705578164 ;
		r[10] =  0.26034596607903982692624246913924   ;   s[10] =  0.47930806784192034614751506172153   ;   w[10] =  0.087807628716603905876759705578164 ;
		r[11] =  0.47930806784192034614751506172153   ;   s[11] =  0.26034596607903982692624246913924   ;   w[11] =  0.087807628716603905876759705578164 ;
		r[12] =  0.33333333333333333333333333333333   ;   s[12] =  0.33333333333333333333333333333333   ;   w[12] = -0.074785022233840875314855627736549 ;
		break;

	case 8:
		r.resize(16); s.resize(16); w.resize(16);
		r[ 0] =  0.0505472283170309754584235505965989 ;   s[ 0] =  0.0505472283170309754584235505965989 ;   w[ 0] =  0.0162292488115990401554629641708902 ;
		r[ 1] =  0.0505472283170309754584235505965989 ;   s[ 1] =  0.8989055433659380867084109922870994 ;   w[ 1] =  0.0162292488115990401554629641708902 ;
		r[ 2] =  0.8989055433659380867084109922870994 ;   s[ 2] =  0.0505472283170309754584235505965989 ;   w[ 2] =  0.0162292488115990401554629641708902 ;
		r[ 3] =  0.170569307751760206622293501491464  ;   s[ 3] =  0.170569307751760206622293501491464  ;   w[ 3] =  0.0516086852673591251408957751460645 ;
		r[ 4] =  0.170569307751760206622293501491464  ;   s[ 4] =  0.6588613844964795740466456663853023 ;   w[ 4] =  0.0516086852673591251408957751460645 ;
		r[ 5] =  0.6588613844964795740466456663853023 ;   s[ 5] =  0.170569307751760206622293501491464  ;   w[ 5] =  0.0516086852673591251408957751460645 ;
		r[ 6] =  0.081414823414553638691870673937956  ;   s[ 6] =  0.081414823414553638691870673937956  ;   w[ 6] =  0.0475458171336423123969480521942921 ;
		r[ 7] =  0.081414823414553638691870673937956  ;   s[ 7] =  0.459292588292723156028815514494169  ;   w[ 7] =  0.0475458171336423123969480521942921 ;
		r[ 8] =  0.459292588292723156028815514494169  ;   s[ 8] =  0.081414823414553638691870673937956  ;   w[ 8] =  0.0475458171336423123969480521942921 ;
		r[ 9] =  0.0083947774099576433215474935423117 ;   s[ 9] =  0.263112829634638113421785786284643  ;   w[ 9] =  0.0136151570872174971324223450369544 ;
		r[10] =  0.0083947774099576433215474935423117 ;   s[10] =  0.728492392955404281241000379176061  ;   w[10] =  0.0136151570872174971324223450369544 ;
		r[11] =  0.263112829634638113421785786284643  ;   s[11] =  0.0083947774099576433215474935423117 ;   w[11] =  0.0136151570872174971324223450369544 ;
		r[12] =  0.263112829634638113421785786284643  ;   s[12] =  0.728492392955404281241000379176061  ;   w[12] =  0.0136151570872174971324223450369544 ;
		r[13] =  0.728492392955404281241000379176061  ;   s[13] =  0.0083947774099576433215474935423117 ;   w[13] =  0.0136151570872174971324223450369544 ;
		r[14] =  0.728492392955404281241000379176061  ;   s[14] =  0.263112829634638113421785786284643  ;   w[14] =  0.0136151570872174971324223450369544 ;
		r[15] =  0.3333333333333333333333333333333333 ;   s[15] =  0.3333333333333333333333333333333333 ;   w[15] =  0.0721578038388935841255455552445323 ;
		break;

	default: return false;
	}
	return true;
}

int Triangle::maxorder()
{
	return 8;
}

