#include <elo.h>
#include <pairing.h>
#include <standing.h>
#include <team.h>
#include <tournament.h>

#include <iostream>

using namespace wmc_sim;

void getTeams(std::vector<Team>& teams) {
	// See data/elo_ratings.ods
	// Data from mtgeloproject.net
	int ratingsArgentina[] = {2054,1608,1587,1497}; Team Argentina("Argentina", ratingsArgentina); teams.push_back(Argentina);
	int ratingsAustralia[] = {1936,1756,1706,1422}; Team Australia("Australia", ratingsAustralia); teams.push_back(Australia);
	int ratingsAustria[] = {1938,1908,1590,1578}; Team Austria("Austria", ratingsAustria); teams.push_back(Austria);
	int ratingsBelarus[] = {1598,1500,1499,1464}; Team Belarus("Belarus", ratingsBelarus); teams.push_back(Belarus);
	int ratingsBelgium[] = {1793,1788,1736,1689}; Team Belgium("Belgium", ratingsBelgium); teams.push_back(Belgium);
	int ratingsBolivia[] = {1568,1560,1523,1445}; Team Bolivia("Bolivia", ratingsBolivia); teams.push_back(Bolivia);
	int ratingsBrazil[] = {2017,1945,1523,1464}; Team Brazil("Brazil", ratingsBrazil); teams.push_back(Brazil);
	int ratingsBulgaria[] = {1611,1520,1500,1500}; Team Bulgaria("Bulgaria", ratingsBulgaria); teams.push_back(Bulgaria);
	int ratingsCanada[] = {1988,1967,1857,1555}; Team Canada("Canada", ratingsCanada); teams.push_back(Canada);
	int ratingsChile[] = {1756,1685,1652,1562}; Team Chile("Chile", ratingsChile); teams.push_back(Chile);
	int ratingsChina[] = {1879,1725,1648,1551}; Team China("China", ratingsChina); teams.push_back(China);
	int ratingsChineseTaipei[] = {1884,1865,1805,1540}; Team ChineseTaipei("Chinese Taipei", ratingsChineseTaipei); teams.push_back(ChineseTaipei);
	int ratingsColombia[] = {1503,1500,1500,1492}; Team Colombia("Colombia", ratingsColombia); teams.push_back(Colombia);
	int ratingsCostaRica[] = {1758,1650,1516,1488}; Team CostaRica("Costa Rica", ratingsCostaRica); teams.push_back(CostaRica);
	int ratingsCroatia[] = {1925,1543,1500,1500}; Team Croatia("Croatia", ratingsCroatia); teams.push_back(Croatia);
	int ratingsCyprus[] = {1746,1500,1500,1364}; Team Cyprus("Cyprus", ratingsCyprus); teams.push_back(Cyprus);
	int ratingsCzechRepublic[] = {2090,1578,1509,1497}; Team CzechRepublic("Czech Republic", ratingsCzechRepublic); teams.push_back(CzechRepublic);
	int ratingsDenmark[] = {1938,1866,1827,1499}; Team Denmark("Denmark", ratingsDenmark); teams.push_back(Denmark);
	int ratingsDominicanRepublic[] = {1756,1544,1514,1475}; Team DominicanRepublic("Dominican Republic", ratingsDominicanRepublic); teams.push_back(DominicanRepublic);
	int ratingsEcuador[] = {1710,1670,1662,1446}; Team Ecuador("Ecuador", ratingsEcuador); teams.push_back(Ecuador);
	int ratingsElSalvador[] = {1626,1557,1500,1500}; Team ElSalvador("El Salvador", ratingsElSalvador); teams.push_back(ElSalvador);
	int ratingsEngland[] = {2108,1613,1500,1495}; Team England("England", ratingsEngland); teams.push_back(England);
	int ratingsEstonia[] = {1802,1658,1500,1500}; Team Estonia("Estonia", ratingsEstonia); teams.push_back(Estonia);
	int ratingsFinland[] = {1877,1747,1613,1575}; Team Finland("Finland", ratingsFinland); teams.push_back(Finland);
	int ratingsFrance[] = {2066,1971,1742,1712}; Team France("France", ratingsFrance); teams.push_back(France);
	int ratingsGermany[] = {1968,1859,1730,1687}; Team Germany("Germany", ratingsGermany); teams.push_back(Germany);
	int ratingsGreece[] = {1955,1594,1570,1500}; Team Greece("Greece", ratingsGreece); teams.push_back(Greece);
	int ratingsGuatemala[] = {1739,1656,1505,1502}; Team Guatemala("Guatemala", ratingsGuatemala); teams.push_back(Guatemala);
	int ratingsHongKong[] = {2059,1626,1571,1500}; Team HongKong("Hong Kong", ratingsHongKong); teams.push_back(HongKong);
	int ratingsHungary[] = {1760,1516,1500,1416}; Team Hungary("Hungary", ratingsHungary); teams.push_back(Hungary);
	int ratingsIceland[] = {1821,1503,1463,1463}; Team Iceland("Iceland", ratingsIceland); teams.push_back(Iceland);
	int ratingsIndonesia[] = {1706,1686,1619,1523}; Team Indonesia("Indonesia", ratingsIndonesia); teams.push_back(Indonesia);
	int ratingsIreland[] = {1664,1662,1639,1500}; Team Ireland("Ireland", ratingsIreland); teams.push_back(Ireland);
	int ratingsIsrael[] = {1759,1500,1500,1500}; Team Israel("Israel", ratingsIsrael); teams.push_back(Israel);
	int ratingsItaly[] = {1874,1834,1739,1649}; Team Italy("Italy", ratingsItaly); teams.push_back(Italy);
	int ratingsJapan[] = {2162,1846,1731,1681}; Team Japan("Japan", ratingsJapan); teams.push_back(Japan);
	int ratingsLatvia[] = {1839,1578,1527,1483}; Team Latvia("Latvia", ratingsLatvia); teams.push_back(Latvia);
	int ratingsLithuania[] = {1771,1537,1534,1481}; Team Lithuania("Lithuania", ratingsLithuania); teams.push_back(Lithuania);
	int ratingsLuxembourg[] = {1886,1662,1615,1536}; Team Luxembourg("Luxembourg", ratingsLuxembourg); teams.push_back(Luxembourg);
	int ratingsMacedonia[] = {1841,1500,1500,1500}; Team Macedonia("Macedonia", ratingsMacedonia); teams.push_back(Macedonia);
	int ratingsMalaysia[] = {1891,1836,1711,1667}; Team Malaysia("Malaysia", ratingsMalaysia); teams.push_back(Malaysia);
	int ratingsMalta[] = {1678,1514,1500,1467}; Team Malta("Malta", ratingsMalta); teams.push_back(Malta);
	int ratingsMexico[] = {1930,1888,1582,1436}; Team Mexico("Mexico", ratingsMexico); teams.push_back(Mexico);
	int ratingsNetherlands[] = {2061,1772,1676,1611}; Team Netherlands("Netherlands", ratingsNetherlands); teams.push_back(Netherlands);
	int ratingsNewZealand[] = {1884,1873,1871,1607}; Team NewZealand("New Zealand", ratingsNewZealand); teams.push_back(NewZealand);
	int ratingsNorthernIreland[] = {1690,1563,1475,1452}; Team NorthernIreland("Northern Ireland", ratingsNorthernIreland); teams.push_back(NorthernIreland);
	int ratingsNorway[] = {1602,1582,1466,1449}; Team Norway("Norway", ratingsNorway); teams.push_back(Norway);
	int ratingsPanama[] = {1669,1627,1626,1590}; Team Panama("Panama", ratingsPanama); teams.push_back(Panama);
	int ratingsParaguay[] = {1602,1561,1500,1500}; Team Paraguay("Paraguay", ratingsParaguay); teams.push_back(Paraguay);
	int ratingsPeru[] = {1639,1580,1539,1500}; Team Peru("Peru", ratingsPeru); teams.push_back(Peru);
	int ratingsPhilippines[] = {1802,1720,1576,1502}; Team Philippines("Philippines", ratingsPhilippines); teams.push_back(Philippines);
	int ratingsPoland[] = {2054,1857,1721,1500}; Team Poland("Poland", ratingsPoland); teams.push_back(Poland);
	int ratingsPortugal[] = {2197,1819,1701,1657}; Team Portugal("Portugal", ratingsPortugal); teams.push_back(Portugal);
	int ratingsPuertoRico[] = {1643,1526,1500,1500}; Team PuertoRico("Puerto Rico", ratingsPuertoRico); teams.push_back(PuertoRico);
	int ratingsRomania[] = {1530,1514,1467,1463}; Team Romania("Romania", ratingsRomania); teams.push_back(Romania);
	int ratingsRussianFederation[] = {1723,1575,1557,1500}; Team RussianFederation("Russian Federation", ratingsRussianFederation); teams.push_back(RussianFederation);
	int ratingsScotland[] = {1775,1576,1574,1473}; Team Scotland("Scotland", ratingsScotland); teams.push_back(Scotland);
	int ratingsSerbia[] = {1885,1661,1500,1500}; Team Serbia("Serbia", ratingsSerbia); teams.push_back(Serbia);
	int ratingsSingapore[] = {1978,1577,1501,1481}; Team Singapore("Singapore", ratingsSingapore); teams.push_back(Singapore);
	int ratingsSlovakia[] = {1960,1759,1732,1524}; Team Slovakia("Slovakia", ratingsSlovakia); teams.push_back(Slovakia);
	int ratingsSlovenia[] = {1898,1549,1545,1500}; Team Slovenia("Slovenia", ratingsSlovenia); teams.push_back(Slovenia);
	int ratingsSouthAfrica[] = {1519,1500,1500,1500}; Team SouthAfrica("South Africa", ratingsSouthAfrica); teams.push_back(SouthAfrica);
	int ratingsSouthKorea[] = {1797,1692,1500,1490}; Team SouthKorea("South Korea", ratingsSouthKorea); teams.push_back(SouthKorea);
	int ratingsSpain[] = {1842,1759,1556,1508}; Team Spain("Spain", ratingsSpain); teams.push_back(Spain);
	int ratingsSweden[] = {1998,1773,1663,1499}; Team Sweden("Sweden", ratingsSweden); teams.push_back(Sweden);
	int ratingsSwitzerland[] = {1950,1863,1825,1481}; Team Switzerland("Switzerland", ratingsSwitzerland); teams.push_back(Switzerland);
	int ratingsThailand[] = {1766,1578,1569,1486}; Team Thailand("Thailand", ratingsThailand); teams.push_back(Thailand);
	int ratingsTurkey[] = {1734,1582,1579,1524}; Team Turkey("Turkey", ratingsTurkey); teams.push_back(Turkey);
	int ratingsUkraine[] = {1952,1571,1503,1500}; Team Ukraine("Ukraine", ratingsUkraine); teams.push_back(Ukraine);
	int ratingsUnitedStates[] = {2050,1862,1816,1515}; Team UnitedStates("United States", ratingsUnitedStates); teams.push_back(UnitedStates);
	int ratingsUruguay[] = {1726,1664,1587,1500}; Team Uruguay("Uruguay", ratingsUruguay); teams.push_back(Uruguay);
	int ratingsVenezuela[] = {1838,1500,1500,1500}; Team Venezuela("Venezuela", ratingsVenezuela); teams.push_back(Venezuela);
	int ratingsWales[] = {1768,1662,1608,1468}; Team Wales("Wales", ratingsWales); teams.push_back(Wales);
}


int main(int argc, char** argv) {
	double elo_denom = 1135.77;
	double draw_chance = 0.01;
	Elo elo(elo_denom, draw_chance);

	std::vector<Team> teams;
	getTeams(teams);

	std::map<Team, std::map<FinalResult, int>> results_accumulator;
	for(Team t : teams) {
		for(int i = 0; i <= int(FinalResult::NotTop48); ++i) {
			results_accumulator[t][FinalResult(i)] = 0;
		}
	}

	int num_sims = 10000;
	while(num_sims > 0) {
		Tournament tournament(teams, &elo);
		tournament.perform();
		
		for(Team t : teams) {
			results_accumulator[t][tournament.results[t]] += 1;
		}

		num_sims--;
	}

	std::cout << "Team";
	for(int i = 0; i <= int(FinalResult::NotTop48); ++i) {
		std::cout << "," << finalResultToString(FinalResult(i));
	}
	std::cout << std::endl;

	for(Team t : teams) {
		std::cout << t;
		for(int i = 0; i <= int(FinalResult::NotTop48); ++i) {
			std::cout << "," << results_accumulator[t][FinalResult(i)];
		}
		std::cout << std::endl;
	}

	return 0;
}
