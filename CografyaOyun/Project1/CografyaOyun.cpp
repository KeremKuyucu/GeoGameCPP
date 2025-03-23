#include <iostream>
#include <fstream>
#include <filesystem>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
//------------------------------------------------------------------------------------------------------------------------- tanımlamalar
using namespace std;	using namespace filesystem;		using namespace sf;
Font font;	Texture bayrak, arkaplan;	Music dogru, yanlis, yenitur,arkafon;	Sprite sprite,sprite2;	Event event;	Text menuText("Menu Text", font, 40);
string komut, yazilanlar, kaliciyazilanlar;
bool amerikakitasi = true, asyakitasi = true, afrikakitasi = true, avrupakitasi = true, okyanusyakitasi = true, antartikakitasi = true, bmuyeligi = true, arkafonsarki=true;
//------------------------------------------------------------------------------------------------------------------------- ulkeler tanımlama
struct Ulkeler {
	string bayrak; string trisim; string enisim; string isim; string baskent; string kita; string url; bool bm; double enlem; double boylam; int dosyaboyut; bool bilgi=false;
	bool ks(const string& yapilantahmin) const { return (yapilantahmin == trisim || yapilantahmin == isim || yapilantahmin == enisim); }
};
vector<Ulkeler> ulke = {
	{"dosyalar/bayraklar/moldova.png", "Moldova", "Moldova", "Moldova", "Chisinau", "Europe", "https://flagcdn.com/w320/md.png", true, 47, 29, 2600},
	{"dosyalar/bayraklar/amerikabirlesikdevletleri.png", "Amerika", "Unitedstates", "Amerikabirlesikdevletleri", "Washingtondc", "Americas", "https://flagcdn.com/w320/us.png", true, 38, -97, 1289},
	{"dosyalar/bayraklar/mayotte.png", "Mayotte", "Mayotte", "Mayotte", "Mamoudzou", "Africa", "https://flagcdn.com/w320/yt.png", false, -12.83, 45.17, 8185},
	{"dosyalar/bayraklar/nauru.png", "Nauru", "Nauru", "Nauru", "Yaren", "Oceania", "https://flagcdn.com/w320/nr.png", true, -0.53, 166.92, 651},
	{"dosyalar/bayraklar/mozambik.png", "Mozambik", "Mozambique", "Mozambik", "Maputo", "Africa", "https://flagcdn.com/w320/mz.png", true, -18.25, 35, 2298},
	{"dosyalar/bayraklar/brezilya.png", "Brezilya", "Brazil", "Brezilya", "Brasília", "Americas", "https://flagcdn.com/w320/br.png", true, -10, -55, 2883},
	{"dosyalar/bayraklar/yesilburun.png", "Yeilburun", "Capeverde", "Yesilburun", "Praia", "Africa", "https://flagcdn.com/w320/cv.png", true, 16.54, -23.04, 909},
	{"dosyalar/bayraklar/ekvatorginesi.png", "Ekvatorginesi", "Equatorialguinea", "Ekvatorginesi", "Malabo", "Africa", "https://flagcdn.com/w320/gq.png", true, 2, 10, 1923},
	{"dosyalar/bayraklar/arnavutluk.png", "Arnavutluk", "Albania", "Arnavutluk", "Tirana", "Europe", "https://flagcdn.com/w320/al.png", true, 41, 20, 3044},
	{"dosyalar/bayraklar/abdvirjinadalari.png", "Abdvirjinadalar", "Unitedstatesvirginislands", "Abdvirjinadalari", "Charlotteamalie", "Americas", "https://flagcdn.com/w320/vi.png", false, 18.35, -64.93, 9362},
	{"dosyalar/bayraklar/niue.png", "Niue", "Niue", "Niue", "Alofi", "Oceania", "https://flagcdn.com/w320/nu.png", false, -19.03, -169.87, 1457},
	{"dosyalar/bayraklar/palau.png", "Palau", "Palau", "Palau", "Ngerulmud", "Oceania", "https://flagcdn.com/w320/pw.png", true, 7.5, 134.5, 738},
	{"dosyalar/bayraklar/nijerya.png", "Nijerya", "Nigeria", "Nijerya", "Abuja", "Africa", "https://flagcdn.com/w320/ng.png", true, 10, 8, 157},
	{"dosyalar/bayraklar/virjinadalari.png", "Virjinadalar", "Britishvirginislands", "Virjinadalari", "Roadtown", "Americas", "https://flagcdn.com/w320/vg.png", false, 18.43, -64.62, 4437},
	{"dosyalar/bayraklar/gambiya.png", "Gambiya", "Gambia", "Gambiya", "Banjul", "Africa", "https://flagcdn.com/w320/gm.png", true, 13.47, -16.57, 248},
	{"dosyalar/bayraklar/somali.png", "Somali", "Somalia", "Somali", "Mogadishu", "Africa", "https://flagcdn.com/w320/so.png", true, 10, 49, 693},
	{"dosyalar/bayraklar/yemen.png", "Yemen", "Yemen", "Yemen", "Sanaa", "Asia", "https://flagcdn.com/w320/ye.png", true, 15, 48, 153},
	{"dosyalar/bayraklar/malezya.png", "Malezya", "Malaysia", "Malezya", "Kualalumpur", "Asia", "https://flagcdn.com/w320/my.png", true, 2.5, 112.5, 1139},
	{"dosyalar/bayraklar/dominika.png", "Dominika", "Dominica", "Dominika", "Roseau", "Americas", "https://flagcdn.com/w320/dm.png", true, 15.42, -61.33, 1715},
	{"dosyalar/bayraklar/birlesikkrallik.png", "Birleikkrallk", "Unitedkingdom", "Birlesikkrallik", "London", "Europe", "https://flagcdn.com/w320/gb.png", true, 54, -2, 980},
	{"dosyalar/bayraklar/madagaskar.png", "Madagaskar", "Madagascar", "Madagaskar", "Antananarivo", "Africa", "https://flagcdn.com/w320/mg.png", true, -20, 47, 266},
	{"dosyalar/bayraklar/sahrademokratikarapcumhuriyeti.png", "Sahrademokratikarapcumhuriyeti", "Westernsahara", "Sahrademokratikarapcumhuriyeti", "Elaaiun", "Africa", "https://flagcdn.com/w320/eh.png", false, 24.5, -13, 1083},
	{"dosyalar/bayraklar/kibris.png", "Kbrs", "Cyprus", "Kibris", "Nicosia", "Europe", "https://flagcdn.com/w320/cy.png", true, 35, 33, 2172},
	{"dosyalar/bayraklar/antiguavebarbuda.png", "Antiguavebarbuda", "Antiguaandbarbuda", "Antiguavebarbuda", "Saintjohns", "Americas", "https://flagcdn.com/w320/ag.png", true, 17.05, -61.8, 2325},
	{"dosyalar/bayraklar/irlanda.png", "Rlanda", "Ireland", "Irlanda", "Dublin", "Europe", "https://flagcdn.com/w320/ie.png", true, 53, -8, 219},
	{"dosyalar/bayraklar/paraguay.png", "Paraguay", "Paraguay", "Paraguay", "Asunción", "Americas", "https://flagcdn.com/w320/py.png", true, -23, -58, 1190},
	{"dosyalar/bayraklar/srilanka.png", "Srilanka", "Srilanka", "Srilanka", "Srijayawardenepurakotte", "Asia", "https://flagcdn.com/w320/lk.png", true, 7, 81, 3493},
	{"dosyalar/bayraklar/guneyafrika.png", "Gneyafrika", "Southafrica", "Guneyafrika", "Pretoriabloemfonteincapetown", "Africa", "https://flagcdn.com/w320/za.png", true, -29, 24, 985},
	{"dosyalar/bayraklar/kuveyt.png", "Kuveyt", "Kuwait", "Kuveyt", "Kuwaitcity", "Asia", "https://flagcdn.com/w320/kw.png", true, 29.5, 45.75, 527},
	{"dosyalar/bayraklar/cezayir.png", "Cezayir", "Algeria", "Cezayir", "Algiers", "Africa", "https://flagcdn.com/w320/dz.png", true, 28, 3, 989},
	{"dosyalar/bayraklar/hirvatistan.png", "Hrvatistan", "Croatia", "Hirvatistan", "Zagreb", "Europe", "https://flagcdn.com/w320/hr.png", true, 45.17, 15.5, 1810},
	{"dosyalar/bayraklar/martinik.png", "Martinik", "Martinique", "Martinik", "Fortdefrance", "Americas", "https://flagcdn.com/w320/mq.png", false, 14.67, -61, 957},
	{"dosyalar/bayraklar/sierraleone.png", "Sierraleone", "Sierraleone", "Sierraleone", "Freetown", "Africa", "https://flagcdn.com/w320/sl.png", true, 8.5, -11.5, 153},
	{"dosyalar/bayraklar/kuzeymarianaadalari.png", "Kuzeymarianaadalar", "Northernmarianaislands", "Kuzeymarianaadalari", "Saipan", "Oceania", "https://flagcdn.com/w320/mp.png", false, 15.2, 145.75, 9029},
	{"dosyalar/bayraklar/ruanda.png", "Ruanda", "Rwanda", "Ruanda", "Kigali", "Africa", "https://flagcdn.com/w320/rw.png", true, -2, 30, 1180},
	{"dosyalar/bayraklar/suriye.png", "Suriye", "Syria", "Suriye", "Damascus", "Asia", "https://flagcdn.com/w320/sy.png", true, 35, 38, 819},
	{"dosyalar/bayraklar/saintvincentvegrenadinler.png", "Saintvincentvegrenadinler", "Saintvincentandthegrenadines", "Saintvincentvegrenadinler", "Kingstown", "Americas", "https://flagcdn.com/w320/vc.png", true, 13.25, -61.2, 1087},
	{"dosyalar/bayraklar/kosova.png", "Kosova", "Kosovo", "Kosova", "Pristina", "Europe", "https://flagcdn.com/w320/xk.png", false, 42.67, 21.17, 1730},
	{"dosyalar/bayraklar/saintlucia.png", "Saintlucia", "Saintlucia", "Saintlucia", "Castries", "Americas", "https://flagcdn.com/w320/lc.png", true, 13.88, -60.97, 1552},
	{"dosyalar/bayraklar/honduras.png", "Honduras", "Honduras", "Honduras", "Tegucigalpa", "Americas", "https://flagcdn.com/w320/hn.png", true, 15, -86.5, 595},
	{"dosyalar/bayraklar/urdun.png", "Rdn", "Jordan", "Urdun", "Amman", "Asia", "https://flagcdn.com/w320/jo.png", true, 31, 36, 658},
	{"dosyalar/bayraklar/tuvalu.png", "Tuvalu", "Tuvalu", "Tuvalu", "Funafuti", "Oceania", "https://flagcdn.com/w320/tv.png", true, -8, 178, 1820},
	{"dosyalar/bayraklar/nepal.png", "Nepal", "Nepal", "Nepal", "Kathmandu", "Asia", "https://flagcdn.com/w320/np.png", true, 28, 84, 3611},
	{"dosyalar/bayraklar/liberya.png", "Liberya", "Liberia", "Liberya", "Monrovia", "Africa", "https://flagcdn.com/w320/lr.png", true, 6.5, -9.5, 606},
	{"dosyalar/bayraklar/heardadasivemcdonaldadalari.png", "Heardadasvemcdonaldadalar", "Heardislandandmcdonaldislands", "Heardadasivemcdonaldadalari", "", "Antarctic", "https://flagcdn.com/w320/hm.png", false, 53.08, 73.5, 1577},
	{"dosyalar/bayraklar/avusturya.png", "Avusturya", "Austria", "Avusturya", "Vienna", "Europe", "https://flagcdn.com/w320/at.png", true, 47.33, 13.33, 118},
	{"dosyalar/bayraklar/guernsey.png", "Guernsey", "Guernsey", "Guernsey", "Stpeterport", "Europe", "https://flagcdn.com/w320/gg.png", false, 49.47, -2.58, 570},
	{"dosyalar/bayraklar/ortaafrikacumhuriyeti.png", "Ortaafrikacumhuriyeti", "Centralafricanrepublic", "Ortaafrikacumhuriyeti", "Bangui", "Africa", "https://flagcdn.com/w320/cf.png", true, 7, 21, 622},
	{"dosyalar/bayraklar/moritanya.png", "Moritanya", "Mauritania", "Moritanya", "Nouakchott", "Africa", "https://flagcdn.com/w320/mr.png", true, 20, -12, 1002},
	{"dosyalar/bayraklar/cibuti.png", "Cibuti", "Djibouti", "Cibuti", "Djibouti", "Africa", "https://flagcdn.com/w320/dj.png", true, 11.5, 43, 1474},
	{"dosyalar/bayraklar/fiji.png", "Fiji", "Fiji", "Fiji", "Suva", "Oceania", "https://flagcdn.com/w320/fj.png", true, 17.71, 178.06, 3250},
	{"dosyalar/bayraklar/norvec.png", "Norve", "Norway", "Norvec", "Oslo", "Europe", "https://flagcdn.com/w320/no.png", true, 62, 10, 323},
	{"dosyalar/bayraklar/letonya.png", "Letonya", "Latvia", "Letonya", "Riga", "Europe", "https://flagcdn.com/w320/lv.png", true, 57, 25, 112},
	{"dosyalar/bayraklar/falklandmalvinaadalari.png", "Falklandmalvinaadalar", "Falklandislands", "Falklandmalvinaadalari", "Stanley", "Americas", "https://flagcdn.com/w320/fk.png", false, -51.75, -59, 5318},
	{"dosyalar/bayraklar/kazakistan.png", "Kazakistan", "Kazakhstan", "Kazakistan", "Nursultan", "Asia", "https://flagcdn.com/w320/kz.png", true, 48.02, 66.92, 2960},
	{"dosyalar/bayraklar/aland.png", "Aland", "Alandislands", "Aland", "Mariehamn", "Europe", "https://flagcdn.com/w320/ax.png", false, 60.12, 19.9, 311},
	{"dosyalar/bayraklar/turkmenistan.png", "Trkmenistan", "Turkmenistan", "Turkmenistan", "Ashgabat", "Asia", "https://flagcdn.com/w320/tm.png", true, 40, 60, 7750},
	{"dosyalar/bayraklar/cocoskeelingadalari.png", "Cocoskeelingadalar", "Cocoskeelingislands", "Cocoskeelingadalari", "Westisland", "Oceania", "https://flagcdn.com/w320/cc.png", false, 12.16, 96.87, 1989},
	{"dosyalar/bayraklar/bulgaristan.png", "Bulgaristan", "Bulgaria", "Bulgaristan", "Sofia", "Europe", "https://flagcdn.com/w320/bg.png", true, 43, 25, 151},
	{"dosyalar/bayraklar/tokelau.png", "Tokelau", "Tokelau", "Tokelau", "Fakaofo", "Oceania", "https://flagcdn.com/w320/tk.png", false, -9, -172, 1418},
	{"dosyalar/bayraklar/yenikaledonya.png", "Yenikaledonya", "Newcaledonia", "Yenikaledonya", "Nouméa", "Oceania", "https://flagcdn.com/w320/nc.png", false, -21.5, 165.5, 1715},
	{"dosyalar/bayraklar/barbados.png", "Barbados", "Barbados", "Barbados", "Bridgetown", "Americas", "https://flagcdn.com/w320/bb.png", true, 13.17, -59.53, 998},
	{"dosyalar/bayraklar/saotomeandprincipe.png", "Saotomeandprincipe", "Saotomeandprincipe", "Saotomeandprincipe", "Saotome", "Africa", "https://flagcdn.com/w320/st.png", true, 1, 7, 1077},
	{"dosyalar/bayraklar/antarktika.png", "Antarktika", "Antarctica", "Antarktika", "", "Antarctic", "https://flagcdn.com/w320/aq.png", false, -90, 0, 1354},
	{"dosyalar/bayraklar/brunei.png", "Brunei", "Brunei", "Brunei", "Bandarseribegawan", "Asia", "https://flagcdn.com/w320/bn.png", true, 4.5, 114.67, 3402},
	{"dosyalar/bayraklar/butan.png", "Butan", "Bhutan", "Butan", "Thimphu", "Asia", "https://flagcdn.com/w320/bt.png", true, 27.5, 90.5, 8230},
	{"dosyalar/bayraklar/kamerun.png", "Kamerun", "Cameroon", "Kamerun", "Yaoundé", "Africa", "https://flagcdn.com/w320/cm.png", true, 6, 12, 637},
	{"dosyalar/bayraklar/arjantin.png", "Arjantin", "Argentina", "Arjantin", "Buenosaires", "Americas", "https://flagcdn.com/w320/ar.png", true, -34, -64, 1578},
	{"dosyalar/bayraklar/azerbaycan.png", "Azerbaycan", "Azerbaijan", "Azerbaycan", "Baku", "Asia", "https://flagcdn.com/w320/az.png", true, 40.5, 47.5, 706},
	{"dosyalar/bayraklar/meksika.png", "Meksika", "Mexico", "Meksika", "Mexicocity", "Americas", "https://flagcdn.com/w320/mx.png", true, 23, -102, 3655},
	{"dosyalar/bayraklar/fas.png", "Fas", "Morocco", "Fas", "Rabat", "Africa", "https://flagcdn.com/w320/ma.png", true, 32, -5, 928},
	{"dosyalar/bayraklar/guatemala.png", "Guatemala", "Guatemala", "Guatemala", "Guatemalacity", "Americas", "https://flagcdn.com/w320/gt.png", true, 15.5, -90.25, 2518},
	{"dosyalar/bayraklar/kenya.png", "Kenya", "Kenya", "Kenya", "Nairobi", "Africa", "https://flagcdn.com/w320/ke.png", true, 1, 38, 1966},
	{"dosyalar/bayraklar/malta.png", "Malta", "Malta", "Malta", "Valletta", "Europe", "https://flagcdn.com/w320/mt.png", true, 35.94, 14.38, 1073},
	{"dosyalar/bayraklar/cekya.png", "Ekya", "Czechia", "Cekya", "Prague", "Europe", "https://flagcdn.com/w320/cz.png", true, 49.75, 15.5, 940},
	{"dosyalar/bayraklar/cebelitarik.png", "Cebelitark", "Gibraltar", "Cebelitarik", "Gibraltar", "Europe", "https://flagcdn.com/w320/gi.png", false, 36.13, -5.35, 2033},
	{"dosyalar/bayraklar/aruba.png", "Aruba", "Aruba", "Aruba", "Oranjestad", "Americas", "https://flagcdn.com/w320/aw.png", false, 12.5, -69.97, 735},
	{"dosyalar/bayraklar/saintbarthelemy.png", "Saintbarthelemy", "Saintbarthelemy", "Saintbarthelemy", "Gustavia", "Americas", "https://flagcdn.com/w320/bl.png", false, 18.5, -63.42, 11667},
	{"dosyalar/bayraklar/monako.png", "Monako", "Monaco", "Monako", "Monaco", "Europe", "https://flagcdn.com/w320/mc.png", true, 43.73, 7.4, 124},
	{"dosyalar/bayraklar/birlesikarapemirlikleri.png", "Birleikarapemirlikleri", "Unitedarabemirates", "Birlesikarapemirlikleri", "Abudhabi", "Asia", "https://flagcdn.com/w320/ae.png", true, 24, 54, 233},
	{"dosyalar/bayraklar/guneysudan.png", "Gneysudan", "Southsudan", "Guneysudan", "Juba", "Africa", "https://flagcdn.com/w320/ss.png", true, 7, 30, 1000},
	{"dosyalar/bayraklar/portoriko.png", "Portoriko", "Puertorico", "Portoriko", "Sanjuan", "Americas", "https://flagcdn.com/w320/pr.png", false, 18.25, -66.5, 1474},
	{"dosyalar/bayraklar/elsalvador.png", "Elsalvador", "Elsalvador", "Elsalvador", "Sansalvador", "Americas", "https://flagcdn.com/w320/sv.png", true, 13.83, -88.92, 2363},
	{"dosyalar/bayraklar/fransa.png", "Fransa", "France", "Fransa", "Paris", "Europe", "https://flagcdn.com/w320/fr.png", true, 46, 2, 253},
	{"dosyalar/bayraklar/nijer.png", "Nijer", "Niger", "Nijer", "Niamey", "Africa", "https://flagcdn.com/w320/ne.png", true, 16, 8, 645},
	{"dosyalar/bayraklar/fildisisahili.png", "Fildiisahili", "Ivorycoast", "Fildisisahili", "Yamoussoukro", "Africa", "https://flagcdn.com/w320/ci.png", true, 8, -5, 252},
	{"dosyalar/bayraklar/guneygeorgiaveguneysandwichadalari.png", "Gneygeorgiavegneysandwichadalar", "Southgeorgia", "Guneygeorgiaveguneysandwichadalari", "Kingedwardpoint", "Antarctic", "https://flagcdn.com/w320/gs.png", false, -54.5, -37, 6026},
	{"dosyalar/bayraklar/botsvana.png", "Botsvana", "Botswana", "Botsvana", "Gaborone", "Africa", "https://flagcdn.com/w320/bw.png", true, -22, 24, 199},
	{"dosyalar/bayraklar/britanyahintokyanusutopraklari.png", "Britanyahintokyanusutopraklar", "Britishindianoceanterritory", "Britanyahintokyanusutopraklari", "Diegogarcia", "Africa", "https://flagcdn.com/w320/io.png", false, -6, 71.5, 7213},
	{"dosyalar/bayraklar/ozbekistan.png", "Zbekistan", "Uzbekistan", "Ozbekistan", "Tashkent", "Asia", "https://flagcdn.com/w320/uz.png", true, 41, 64, 760},
	{"dosyalar/bayraklar/tunus.png", "Tunus", "Tunisia", "Tunus", "Tunis", "Africa", "https://flagcdn.com/w320/tn.png", true, 34, 9, 1128},
	{"dosyalar/bayraklar/hongkong.png", "Hongkong", "Hongkong", "Hongkong", "Cityofvictoria", "Asia", "https://flagcdn.com/w320/hk.png", false, 22.27, 114.19, 2045},
	{"dosyalar/bayraklar/kuzeymakedonya.png", "Kuzeymakedonya", "Northmacedonia", "Kuzeymakedonya", "Skopje", "Europe", "https://flagcdn.com/w320/mk.png", true, 41.83, 22, 1613},
	{"dosyalar/bayraklar/surinam.png", "Surinam", "Suriname", "Surinam", "Paramaribo", "Americas", "https://flagcdn.com/w320/sr.png", true, 4, -56, 686},
	{"dosyalar/bayraklar/belcika.png", "Belika", "Belgium", "Belcika", "Brussels", "Europe", "https://flagcdn.com/w320/be.png", true, 50.83, 4, 292},
	{"dosyalar/bayraklar/amerikansamoasi.png", "Amerikansamoas", "Americansamoa", "Amerikansamoasi", "Pagopago", "Oceania", "https://flagcdn.com/w320/as.png", false, -14.33, -170, 3763},
	{"dosyalar/bayraklar/solomonadalari.png", "Solomonadalar", "Solomonislands", "Solomonadalari", "Honiara", "Oceania", "https://flagcdn.com/w320/sb.png", true, -8, 159, 1446},
	{"dosyalar/bayraklar/ukrayna.png", "Ukrayna", "Ukraine", "Ukrayna", "Kyiv", "Europe", "https://flagcdn.com/w320/ua.png", true, 49, 32, 146},
	{"dosyalar/bayraklar/finlandiya.png", "Finlandiya", "Finland", "Finlandiya", "Helsinki", "Europe", "https://flagcdn.com/w320/fi.png", true, 64, 26, 240},
	{"dosyalar/bayraklar/burkinafaso.png", "Burkinafaso", "Burkinafaso", "Burkinafaso", "Ouagadougou", "Africa", "https://flagcdn.com/w320/bf.png", true, 13, -2, 702},
	{"dosyalar/bayraklar/bosnahersek.png", "Bosnahersek", "Bosniaandherzegovina", "Bosnahersek", "Sarajevo", "Europe", "https://flagcdn.com/w320/ba.png", true, 44, 18, 1197},
	{"dosyalar/bayraklar/iran.png", "Ran", "Iran", "Iran", "Tehran", "Asia", "https://flagcdn.com/w320/ir.png", true, 32, 53, 2156},
	{"dosyalar/bayraklar/kuba.png", "Kba", "Cuba", "Kuba", "Havana", "Americas", "https://flagcdn.com/w320/cu.png", true, 21.5, -80, 1059},
	{"dosyalar/bayraklar/eritre.png", "Eritre", "Eritrea", "Eritre", "Asmara", "Africa", "https://flagcdn.com/w320/er.png", true, 15, 39, 2447},
	{"dosyalar/bayraklar/slovakya.png", "Slovakya", "Slovakia", "Slovakya", "Bratislava", "Europe", "https://flagcdn.com/w320/sk.png", true, 48.67, 19.5, 1366},
	{"dosyalar/bayraklar/litvanya.png", "Litvanya", "Lithuania", "Litvanya", "Vilnius", "Europe", "https://flagcdn.com/w320/lt.png", true, 56, 24, 151},
	{"dosyalar/bayraklar/saintmartin.png", "Saintmartin", "Saintmartin", "Saintmartin", "Marigot", "Americas", "https://flagcdn.com/w320/mf.png", false, 18.07, 63.05, 253},
	{"dosyalar/bayraklar/pitcairnadalari.png", "Pitcairnadalar", "Pitcairnislands", "Pitcairnadalari", "Adamstown", "Oceania", "https://flagcdn.com/w320/pn.png", false, -25.07, -130.1, 4822},
	{"dosyalar/bayraklar/ginebissau.png", "Ginebissau", "Guineabissau", "Ginebissau", "Bissau", "Africa", "https://flagcdn.com/w320/gw.png", false, 12, -15, 519},
	{"dosyalar/bayraklar/montserrat.png", "Montserrat", "Montserrat", "Montserrat", "Plymouth", "Americas", "https://flagcdn.com/w320/ms.png", false, 16.75, -62.2, 2440},
	{"dosyalar/bayraklar/turkiye.png", "Trkiye", "Turkey", "Turkiye", "Ankara", "Asia", "https://flagcdn.com/w320/tr.png", true, 39, 35, 947},
	{"dosyalar/bayraklar/filipinler.png", "Filipinler", "Philippines", "Filipinler", "Manila", "Asia", "https://flagcdn.com/w320/ph.png", true, 13, 122, 1665},
	{"dosyalar/bayraklar/vanuatu.png", "Vanuatu", "Vanuatu", "Vanuatu", "Portvila", "Oceania", "https://flagcdn.com/w320/vu.png", true, -16, 167, 1682},
	{"dosyalar/bayraklar/bolivya.png", "Bolivya", "Bolivia", "Bolivya", "Sucre", "Americas", "https://flagcdn.com/w320/bo.png", true, -17, -65, 3978},
	{"dosyalar/bayraklar/saintkittsvenevis.png", "Saintkittsvenevis", "Saintkittsandnevis", "Saintkittsvenevis", "Basseterre", "Americas", "https://flagcdn.com/w320/kn.png", true, 17.33, -62.75, 2098},
	{"dosyalar/bayraklar/romanya.png", "Romanya", "Romania", "Romanya", "Bucharest", "Europe", "https://flagcdn.com/w320/ro.png", true, 46, 25, 253},
	{"dosyalar/bayraklar/kambocya.png", "Kamboya", "Cambodia", "Kambocya", "Phnompenh", "Asia", "https://flagcdn.com/w320/kh.png", true, 13, 105, 2613},
	{"dosyalar/bayraklar/zimbabve.png", "Zimbabve", "Zimbabwe", "Zimbabve", "Harare", "Africa", "https://flagcdn.com/w320/zw.png", true, -20, 30, 1548},
	{"dosyalar/bayraklar/jersey.png", "Jersey", "Jersey", "Jersey", "Sainthelier", "Europe", "https://flagcdn.com/w320/je.png", false, 49.25, -2.17, 2978},
	{"dosyalar/bayraklar/kirgizistan.png", "Krgzistan", "Kyrgyzstan", "Kirgizistan", "Bishkek", "Asia", "https://flagcdn.com/w320/kg.png", true, 41, 75, 3399},
	{"dosyalar/bayraklar/karayiphollandasi.png", "Karayiphollandas", "Caribbeannetherlands", "Karayiphollandasi", "Kralendijk", "Americas", "https://flagcdn.com/w320/bq.png", false, 12.18, -68.25, 2386},
	{"dosyalar/bayraklar/guyana.png", "Guyana", "Guyana", "Guyana", "Georgetown", "Americas", "https://flagcdn.com/w320/gy.png", true, 5, -59, 1438},
	{"dosyalar/bayraklar/amerikabirlesikdevletlerikucukdisadalari.png", "Amerikabirleikdevletlerikkdadalar", "Unitedstatesminoroutlyingislands", "Amerikabirlesikdevletlerikucukdisadalari", "Washingtondc", "Americas", "https://flagcdn.com/w320/um.png", false, 19.3, 166.63, 1289},
	{"dosyalar/bayraklar/ermenistan.png", "Ermenistan", "Armenia", "Ermenistan", "Yerevan", "Asia", "https://flagcdn.com/w320/am.png", true, 40, 45, 198},
	{"dosyalar/bayraklar/lubnan.png", "Lbnan", "Lebanon", "Lubnan", "Beirut", "Asia", "https://flagcdn.com/w320/lb.png", true, 33.83, 35.83, 1239},
	{"dosyalar/bayraklar/karadag.png", "Karada", "Montenegro", "Karadag", "Podgorica", "Europe", "https://flagcdn.com/w320/me.png", true, 42.5, 19.3, 3568},
	{"dosyalar/bayraklar/gronland.png", "Grnland", "Greenland", "Gronland", "Nuuk", "Americas", "https://flagcdn.com/w320/gl.png", false, 72, -40, 1104},
	{"dosyalar/bayraklar/papuayenigine.png", "Papuayenigine", "Papuanewguinea", "Papuayenigine", "Portmoresby", "Oceania", "https://flagcdn.com/w320/pg.png", true, -6, 147, 2772},
	{"dosyalar/bayraklar/zambiya.png", "Zambiya", "Zambia", "Zambiya", "Lusaka", "Africa", "https://flagcdn.com/w320/zm.png", true, -15, 30, 1062},
	{"dosyalar/bayraklar/trinidadvetobago.png", "Trinidadvetobago", "Trinidadandtobago", "Trinidadvetobago", "Portofspain", "Americas", "https://flagcdn.com/w320/tt.png", true, 10.69, -61.22, 1236},
	{"dosyalar/bayraklar/fransizguneyveantarktikatopraklari.png", "Franszgneyveantarktikatopraklar", "Frenchsouthernandantarcticlands", "Fransizguneyveantarktikatopraklari", "Portauxfrançais", "Antarctic", "https://flagcdn.com/w320/tf.png", false, -49.25, 69.17, 1257},
	{"dosyalar/bayraklar/peru.png", "Peru", "Peru", "Peru", "Lima", "Americas", "https://flagcdn.com/w320/pe.png", true, -10, -76, 172},
	{"dosyalar/bayraklar/isvec.png", "Sve", "Sweden", "Isvec", "Stockholm", "Europe", "https://flagcdn.com/w320/se.png", true, 62, 15, 142},
	{"dosyalar/bayraklar/sudan.png", "Sudan", "Sudan", "Sudan", "Khartoum", "Africa", "https://flagcdn.com/w320/sd.png", true, 15, 30, 744},
	{"dosyalar/bayraklar/saintpierrevemiquelon.png", "Saintpierrevemiquelon", "Saintpierreandmiquelon", "Saintpierrevemiquelon", "Saintpierre", "Americas", "https://flagcdn.com/w320/pm.png", false, 46.83, -56.33, 14300},
	{"dosyalar/bayraklar/umman.png", "Umman", "Oman", "Umman", "Muscat", "Asia", "https://flagcdn.com/w320/om.png", true, 21, 57, 789},
	{"dosyalar/bayraklar/hindistan.png", "Hindistan", "India", "Hindistan", "Newdelhi", "Asia", "https://flagcdn.com/w320/in.png", true, 20, 77, 1254},
	{"dosyalar/bayraklar/tayvan.png", "Tayvan", "Taiwan", "Tayvan", "Taipei", "Asia", "https://flagcdn.com/w320/tw.png", false, 23.5, 121, 1352},
	{"dosyalar/bayraklar/mogolistan.png", "Moolistan", "Mongolia", "Mogolistan", "Ulanbator", "Asia", "https://flagcdn.com/w320/mn.png", true, 46, 105, 796},
	{"dosyalar/bayraklar/senegal.png", "Senegal", "Senegal", "Senegal", "Dakar", "Africa", "https://flagcdn.com/w320/sn.png", true, 14, -14, 681},
	{"dosyalar/bayraklar/tanzanya.png", "Tanzanya", "Tanzania", "Tanzanya", "Dodoma", "Africa", "https://flagcdn.com/w320/tz.png", true, -6, 35, 1191},
	{"dosyalar/bayraklar/kanada.png", "Kanada", "Canada", "Kanada", "Ottawa", "Americas", "https://flagcdn.com/w320/ca.png", true, 60, -95, 1317},
	{"dosyalar/bayraklar/kostarika.png", "Kostarika", "Costarica", "Kostarika", "Sanjosé", "Americas", "https://flagcdn.com/w320/cr.png", true, 10, -84, 1665},
	{"dosyalar/bayraklar/cin.png", "In", "China", "Cin", "Beijing", "Asia", "https://flagcdn.com/w320/cn.png", true, 35, 105, 955},
	{"dosyalar/bayraklar/kolombiya.png", "Kolombiya", "Colombia", "Kolombiya", "Bogotá", "Americas", "https://flagcdn.com/w320/co.png", true, 4, -72, 231},
	{"dosyalar/bayraklar/myanmar.png", "Myanmar", "Myanmar", "Myanmar", "Naypyidaw", "Asia", "https://flagcdn.com/w320/mm.png", true, 22, 98, 1315},
	{"dosyalar/bayraklar/rusya.png", "Rusya", "Russia", "Rusya", "Moscow", "Europe", "https://flagcdn.com/w320/ru.png", true, 60, 100, 153},
	{"dosyalar/bayraklar/kuzeykore.png", "Kuzeykore", "Northkorea", "Kuzeykore", "Pyongyang", "Asia", "https://flagcdn.com/w320/kp.png", true, 40, 127, 1133},
	{"dosyalar/bayraklar/caymanadalari.png", "Caymanadalar", "Caymanislands", "Caymanadalari", "Georgetown", "Americas", "https://flagcdn.com/w320/ky.png", false, 19.31, -81.25, 4625},
	{"dosyalar/bayraklar/bouvetadasi.png", "Bouvetadas", "Bouvetisland", "Bouvetadasi", "", "Antarctic", "https://flagcdn.com/w320/bv.png", false, 54.42, 3.35, 323},
	{"dosyalar/bayraklar/belarus.png", "Belarus", "Belarus", "Belarus", "Minsk", "Europe", "https://flagcdn.com/w320/by.png", true, 53, 28, 1717},
	{"dosyalar/bayraklar/portekiz.png", "Portekiz", "Portugal", "Portekiz", "Lisbon", "Europe", "https://flagcdn.com/w320/pt.png", true, 39.5, -8, 4980},
	{"dosyalar/bayraklar/esvatini.png", "Esvatini", "Eswatini", "Esvatini", "Mbabane", "Africa", "https://flagcdn.com/w320/sz.png", true, -26.5, 31.5, 2803},
	{"dosyalar/bayraklar/polonya.png", "Polonya", "Poland", "Polonya", "Warsaw", "Europe", "https://flagcdn.com/w320/pl.png", true, 52, 20, 119},
	{"dosyalar/bayraklar/isvicre.png", "Svire", "Switzerland", "Isvicre", "Bern", "Europe", "https://flagcdn.com/w320/ch.png", true, 47, 8, 154},
	{"dosyalar/bayraklar/kongocumhuriyeti.png", "Kongocumhuriyeti", "Republicofthecongo", "Kongocumhuriyeti", "Brazzaville", "Africa", "https://flagcdn.com/w320/cg.png", true, -1, 15, 980},
	{"dosyalar/bayraklar/venezuela.png", "Venezuela", "Venezuela", "Venezuela", "Caracas", "Americas", "https://flagcdn.com/w320/ve.png", true, 8, -66, 906},
	{"dosyalar/bayraklar/panama.png", "Panama", "Panama", "Panama", "Panamacity", "Americas", "https://flagcdn.com/w320/pa.png", true, 9, -80, 1123},
	{"dosyalar/bayraklar/hollanda.png", "Hollanda", "Netherlands", "Hollanda", "Amsterdam", "Europe", "https://flagcdn.com/w320/nl.png", true, 52.5, 5.75, 153},
	{"dosyalar/bayraklar/bagimsizsamoadevleti.png", "Bamszsamoadevleti", "Samoa", "Bagimsizsamoadevleti", "Apia", "Oceania", "https://flagcdn.com/w320/ws.png", true, -13.58, -172.33, 699},
	{"dosyalar/bayraklar/danimarka.png", "Danimarka", "Denmark", "Danimarka", "Copenhagen", "Europe", "https://flagcdn.com/w320/dk.png", true, 56, 10, 292},
	{"dosyalar/bayraklar/luksemburg.png", "Lksemburg", "Luxembourg", "Luksemburg", "Luxembourg", "Europe", "https://flagcdn.com/w320/lu.png", true, 49.75, 6.17, 151},
	{"dosyalar/bayraklar/faroeadalari.png", "Faroeadalar", "Faroeislands", "Faroeadalari", "Tórshavn", "Europe", "https://flagcdn.com/w320/fo.png", false, 62, -7, 321},
	{"dosyalar/bayraklar/slovenya.png", "Slovenya", "Slovenia", "Slovenya", "Ljubljana", "Europe", "https://flagcdn.com/w320/si.png", true, 46.12, 14.82, 930},
	{"dosyalar/bayraklar/togo.png", "Togo", "Togo", "Togo", "Lomé", "Africa", "https://flagcdn.com/w320/tg.png", true, 8, 1.17, 751},
	{"dosyalar/bayraklar/tayland.png", "Tayland", "Thailand", "Tayland", "Bangkok", "Asia", "https://flagcdn.com/w320/th.png", true, 15, 100, 172},
	{"dosyalar/bayraklar/wallisvefutunaadalaribolgesi.png", "Wallisvefutunaadalarblgesi", "Wallisandfutuna", "Wallisvefutunaadalaribolgesi", "Matautu", "Oceania", "https://flagcdn.com/w320/wf.png", false, -13.3, -176.2, 669},
	{"dosyalar/bayraklar/bahamalar.png", "Bahamalar", "Bahamas", "Bahamalar", "Nassau", "Americas", "https://flagcdn.com/w320/bs.png", true, 25.03, -77.4, 735},
	{"dosyalar/bayraklar/tonga.png", "Tonga", "Tonga", "Tonga", "Nukualofa", "Oceania", "https://flagcdn.com/w320/to.png", true, -20, -175, 163},
	{"dosyalar/bayraklar/yunanistan.png", "Yunanistan", "Greece", "Yunanistan", "Athens", "Europe", "https://flagcdn.com/w320/gr.png", true, 39, 22, 306},
	{"dosyalar/bayraklar/sanmarino.png", "Sanmarino", "Sanmarino", "Sanmarino", "Cityofsanmarino", "Europe", "https://flagcdn.com/w320/sm.png", true, 43.77, 12.42, 7872},
	{"dosyalar/bayraklar/reunion.png", "Reunion", "Reunion", "Reunion", "Saintdenis", "Africa", "https://flagcdn.com/w320/re.png", false, -21.15, 55.5, 2106},
	{"dosyalar/bayraklar/vatikan.png", "Vatikan", "Vaticancity", "Vatikan", "Vaticancity", "Europe", "https://flagcdn.com/w320/va.png", false, 41.9, 12.45, 7956},
	{"dosyalar/bayraklar/burundi.png", "Burundi", "Burundi", "Burundi", "Gitega", "Africa", "https://flagcdn.com/w320/bi.png", true, -3.5, 30, 1841},
	{"dosyalar/bayraklar/bahreyn.png", "Bahreyn", "Bahrain", "Bahreyn", "Manama", "Asia", "https://flagcdn.com/w320/bh.png", true, 26, 50.55, 827},
	{"dosyalar/bayraklar/marshalladalari.png", "Marshalladalar", "Marshallislands", "Marshalladalari", "Majuro", "Oceania", "https://flagcdn.com/w320/mh.png", true, 9, 168, 2699},
	{"dosyalar/bayraklar/turksvecaicosadalari.png", "Turksvecaicosadalar", "Turksandcaicosislands", "Turksvecaicosadalari", "Cockburntown", "Americas", "https://flagcdn.com/w320/tc.png", false, 21.75, -71.58, 2293},
	{"dosyalar/bayraklar/manadasi.png", "Manadas", "Isleofman", "Manadasi", "Douglas", "Europe", "https://flagcdn.com/w320/im.png", false, 54.25, -4.5, 2201},
	{"dosyalar/bayraklar/haiti.png", "Haiti", "Haiti", "Haiti", "Portauprince", "Americas", "https://flagcdn.com/w320/ht.png", true, 19, -72.42, 1972},
	{"dosyalar/bayraklar/afganistan.png", "Afganistan", "Afghanistan", "Afganistan", "Kabul", "Asia", "https://upload.wikimedia.org/wikipedia/commons/thumb/5/5c/Flag_of_the_Taliban.svg/320px-Flag_of_the_Taliban.svg.png", true, 33, 65, 8285},
	{"dosyalar/bayraklar/israil.png", "Srail", "Israel", "Israil", "Jerusalem", "Asia", "https://flagcdn.com/w320/il.png", true, 31.47, 35.13, 893},
	{"dosyalar/bayraklar/libya.png", "Libya", "Libya", "Libya", "Tripoli", "Africa", "https://flagcdn.com/w320/ly.png", true, 25, 17, 579},
	{"dosyalar/bayraklar/uruguay.png", "Uruguay", "Uruguay", "Uruguay", "Montevideo", "Americas", "https://flagcdn.com/w320/uy.png", true, -33, -56, 2392},
	{"dosyalar/bayraklar/norfolkadasi.png", "Norfolkadas", "Norfolkisland", "Norfolkadasi", "Kingston", "Oceania", "https://flagcdn.com/w320/nf.png", false, -29.03, 167.95, 2349},
	{"dosyalar/bayraklar/nikaragua.png", "Nikaragua", "Nicaragua", "Nikaragua", "Managua", "Americas", "https://flagcdn.com/w320/ni.png", true, 13, -85, 1481},
	{"dosyalar/bayraklar/cookadalari.png", "Cookadalar", "Cookislands", "Cookadalari", "Avarua", "Oceania", "https://flagcdn.com/w320/ck.png", false, -21.23, -159.77, 2699},
	{"dosyalar/bayraklar/laos.png", "Laos", "Laos", "Laos", "Vientiane", "Asia", "https://flagcdn.com/w320/la.png", true, 18, 105, 666},
	{"dosyalar/bayraklar/christmasadasi.png", "Christmasadas", "Christmasisland", "Christmasadasi", "Flyingfishcove", "Oceania", "https://flagcdn.com/w320/cx.png", false, -10.5, 105.67, 2256},
	{"dosyalar/bayraklar/sainthelena.png", "Sainthelena", "Sainthelenaascensionandtristandacunha", "Sainthelena", "Jamestown", "Africa", "https://flagcdn.com/w320/sh.png", false, -15.95, -5.72, 2484},
	{"dosyalar/bayraklar/anguilla.png", "Anguilla", "Anguilla", "Anguilla", "Thevalley", "Americas", "https://flagcdn.com/w320/ai.png", false, 18.25, -63.17, 1929},
	{"dosyalar/bayraklar/mikronezya.png", "Mikronezya", "Micronesia", "Mikronezya", "Palikir", "Oceania", "https://flagcdn.com/w320/fm.png", true, 6.92, 158.25, 676},
	{"dosyalar/bayraklar/almanya.png", "Almanya", "Germany", "Almanya", "Berlin", "Europe", "https://flagcdn.com/w320/de.png", true, 51, 9, 151},
	{"dosyalar/bayraklar/guam.png", "Guam", "Guam", "Guam", "Hagåtña", "Oceania", "https://flagcdn.com/w320/gu.png", false, 13.47, 144.78, 2205},
	{"dosyalar/bayraklar/kiribati.png", "Kiribati", "Kiribati", "Kiribati", "Southtarawa", "Oceania", "https://flagcdn.com/w320/ki.png", true, 1.42, 173, 3872},
	{"dosyalar/bayraklar/sintmaarten.png", "Sintmaarten", "Sintmaarten", "Sintmaarten", "Philipsburg", "Americas", "https://flagcdn.com/w320/sx.png", false, 18.03, -63.05, 3972},
	{"dosyalar/bayraklar/ispanya.png", "Spanya", "Spain", "Ispanya", "Madrid", "Europe", "https://flagcdn.com/w320/es.png", true, 40, -4, 3623},
	{"dosyalar/bayraklar/jamaika.png", "Jamaika", "Jamaica", "Jamaika", "Kingston", "Americas", "https://flagcdn.com/w320/jm.png", true, 18.25, -77.5, 972},
	{"dosyalar/bayraklar/filistin.png", "Filistin", "Palestine", "Filistin", "Ramallahjerusalem", "Asia", "https://flagcdn.com/w320/ps.png", false, 31.9, 35.2, 689},
	{"dosyalar/bayraklar/fransizguyanasi.png", "Franszguyanas", "Frenchguiana", "Fransizguyanasi", "Cayenne", "Americas", "https://flagcdn.com/w320/gf.png", false, 4, -53, 1316},
	{"dosyalar/bayraklar/andorra.png", "Andorra", "Andorra", "Andorra", "Andorralavella", "Europe", "https://flagcdn.com/w320/ad.png", true, 42.5, 1.5, 3895},
	{"dosyalar/bayraklar/sili.png", "Ili", "Chile", "Sili", "Santiago", "Americas", "https://flagcdn.com/w320/cl.png", true, -30, -71, 578},
	{"dosyalar/bayraklar/lesotho.png", "Lesotho", "Lesotho", "Lesotho", "Maseru", "Africa", "https://flagcdn.com/w320/ls.png", true, -29.5, 28.5, 1065},
	{"dosyalar/bayraklar/avustralya.png", "Avustralya", "Australia", "Avustralya", "Canberra", "Oceania", "https://flagcdn.com/w320/au.png", true, -27, 133, 1618},
	{"dosyalar/bayraklar/grenada.png", "Grenada", "Grenada", "Grenada", "Stgeorges", "Americas", "https://flagcdn.com/w320/gd.png", true, 12.12, -61.67, 1950},
	{"dosyalar/bayraklar/gana.png", "Gana", "Ghana", "Gana", "Accra", "Africa", "https://flagcdn.com/w320/gh.png", true, 8, -2, 639},
	{"dosyalar/bayraklar/seyseller.png", "Seyeller", "Seychelles", "Seyseller", "Victoria", "Africa", "https://flagcdn.com/w320/sc.png", true, -4.58, 55.67, 1411},
	{"dosyalar/bayraklar/angola.png", "Angola", "Angola", "Angola", "Luanda", "Africa", "https://flagcdn.com/w320/ao.png", true, -12.5, 18.5, 1581},
	{"dosyalar/bayraklar/bermuda.png", "Bermuda", "Bermuda", "Bermuda", "Hamilton", "Americas", "https://flagcdn.com/w320/bm.png", false, 32.33, -64.75, 3942},
	{"dosyalar/bayraklar/pakistan.png", "Pakistan", "Pakistan", "Pakistan", "Islamabad", "Asia", "https://flagcdn.com/w320/pk.png", true, 30, 70, 1281},
	{"dosyalar/bayraklar/mali.png", "Mali", "Mali", "Mali", "Bamako", "Africa", "https://flagcdn.com/w320/ml.png", true, 17, -4, 253},
	{"dosyalar/bayraklar/suudiarabistan.png", "Suudiarabistan", "Saudiarabia", "Suudiarabistan", "Riyadh", "Asia", "https://flagcdn.com/w320/sa.png", true, 25, 45, 3003},
	{"dosyalar/bayraklar/curacao.png", "Curaao", "Curaçao", "Curacao", "Willemstad", "Americas", "https://flagcdn.com/w320/cw.png", false, 12.12, -68.93, 643},
	{"dosyalar/bayraklar/guneykore.png", "Gneykore", "Southkorea", "Guneykore", "Seoul", "Asia", "https://flagcdn.com/w320/kr.png", true, 37, 127.5, 2667},
	{"dosyalar/bayraklar/etiyopya.png", "Etiyopya", "Ethiopia", "Etiyopya", "Addisababa", "Africa", "https://flagcdn.com/w320/et.png", true, 8, 38, 1887},
	{"dosyalar/bayraklar/guadeloupe.png", "Guadeloupe", "Guadeloupe", "Guadeloupe", "Basseterre", "Americas", "https://flagcdn.com/w320/gp.png", false, 16.25, -61.58, 5294},
	{"dosyalar/bayraklar/banglades.png", "Banglade", "Bangladesh", "Banglades", "Dhaka", "Asia", "https://flagcdn.com/w320/bd.png", true, 24, 90, 807},
	{"dosyalar/bayraklar/yenizelanda.png", "Yenizelanda", "Newzealand", "Yenizelanda", "Wellington", "Oceania", "https://flagcdn.com/w320/nz.png", true, -41, 174, 1564},
	{"dosyalar/bayraklar/komorlar.png", "Komorlar", "Comoros", "Komorlar", "Moroni", "Africa", "https://flagcdn.com/w320/km.png", true, -12.17, 44.25, 1587},
	{"dosyalar/bayraklar/belize.png", "Belize", "Belize", "Belize", "Belmopan", "Americas", "https://flagcdn.com/w320/bz.png", true, 17.25, -88.75, 6797},
	{"dosyalar/bayraklar/uganda.png", "Uganda", "Uganda", "Uganda", "Kampala", "Africa", "https://flagcdn.com/w320/ug.png", true, 1, 32, 1457},
	{"dosyalar/bayraklar/singapur.png", "Singapur", "Singapore", "Singapur", "Singapore", "Asia", "https://flagcdn.com/w320/sg.png", true, 1.37, 103.8, 974},
	{"dosyalar/bayraklar/lihtenstayn.png", "Lihtentayn", "Liechtenstein", "Lihtenstayn", "Vaduz", "Europe", "https://flagcdn.com/w320/li.png", true, 47.27, 9.53, 1336},
	{"dosyalar/bayraklar/macaristan.png", "Macaristan", "Hungary", "Macaristan", "Budapest", "Europe", "https://flagcdn.com/w320/hu.png", true, 47, 20, 199},
	{"dosyalar/bayraklar/izlanda.png", "Zlanda", "Iceland", "Izlanda", "Reykjavik", "Europe", "https://flagcdn.com/w320/is.png", true, 65, -18, 330},
	{"dosyalar/bayraklar/tacikistan.png", "Tacikistan", "Tajikistan", "Tacikistan", "Dushanbe", "Asia", "https://flagcdn.com/w320/tj.png", true, 39, 71, 874},
	{"dosyalar/bayraklar/namibya.png", "Namibya", "Namibia", "Namibya", "Windhoek", "Africa", "https://flagcdn.com/w320/na.png", true, -22, 17, 1896},
	{"dosyalar/bayraklar/dogutimor.png", "Doutimor", "Timorleste", "Dogutimor", "Dili", "Asia", "https://flagcdn.com/w320/tl.png", true, -8.83, 125.92, 1305},
	{"dosyalar/bayraklar/misir.png", "Msr", "Egypt", "Misir", "Cairo", "Africa", "https://flagcdn.com/w320/eg.png", true, 27, 30, 1198},
	{"dosyalar/bayraklar/sirbistan.png", "Srbistan", "Serbia", "Sirbistan", "Belgrade", "Europe", "https://flagcdn.com/w320/rs.png", true, 44, 21, 6204},
	{"dosyalar/bayraklar/mauritius.png", "Mauritius", "Mauritius", "Mauritius", "Portlouis", "Africa", "https://flagcdn.com/w320/mu.png", true, -20.28, 57.55, 245},
	{"dosyalar/bayraklar/makao.png", "Makao", "Macau", "Makao", "", "Asia", "https://flagcdn.com/w320/mo.png", false, 22.17, 113.55, 2255},
	{"dosyalar/bayraklar/fransizpolinezyasi.png", "Franszpolinezyas", "Frenchpolynesia", "Fransizpolinezyasi", "Papeete", "Oceania", "https://flagcdn.com/w320/pf.png", false, 17.68, 149.41, 2561},
	{"dosyalar/bayraklar/maldivler.png", "Maldivler", "Maldives", "Maldivler", "Malé", "Asia", "https://flagcdn.com/w320/mv.png", true, 3.25, 73, 704},
	{"dosyalar/bayraklar/endonezya.png", "Endonezya", "Indonesia", "Endonezya", "Jakarta", "Asia", "https://flagcdn.com/w320/id.png", true, -5, 120, 146},
	{"dosyalar/bayraklar/demokratikkongocumhuriyeti.png", "Demokratikkongocumhuriyeti", "Drcongo", "Demokratikkongocumhuriyeti", "Kinshasa", "Africa", "https://flagcdn.com/w320/cd.png", true, 0, 25, 1486},
	{"dosyalar/bayraklar/estonya.png", "Estonya", "Estonia", "Estonya", "Tallinn", "Europe", "https://flagcdn.com/w320/ee.png", true, 59, 26, 153},
	{"dosyalar/bayraklar/vietnam.png", "Vietnam", "Vietnam", "Vietnam", "Hanoi", "Asia", "https://flagcdn.com/w320/vn.png", true, 16.17, 107.83, 913},
	{"dosyalar/bayraklar/italya.png", "Talya", "Italy", "Italya", "Rome", "Europe", "https://flagcdn.com/w320/it.png", true, 42.83, 12.83, 253},
	{"dosyalar/bayraklar/gine.png", "Gine", "Guinea", "Gine", "Conakry", "Africa", "https://flagcdn.com/w320/gn.png", true, 11, -10, 253},
	{"dosyalar/bayraklar/cad.png", "Ad", "Chad", "Cad", "Ndjamena", "Africa", "https://flagcdn.com/w320/td.png", true, 15, 19, 253},
	{"dosyalar/bayraklar/ekvador.png", "Ekvador", "Ecuador", "Ekvador", "Quito", "Americas", "https://flagcdn.com/w320/ec.png", true, -2, -77.5, 5052},
	{"dosyalar/bayraklar/gurcistan.png", "Grcistan", "Georgia", "Gurcistan", "Tbilisi", "Asia", "https://flagcdn.com/w320/ge.png", true, 42, 43.5, 1046},
	{"dosyalar/bayraklar/malavi.png", "Malavi", "Malawi", "Malavi", "Lilongwe", "Africa", "https://flagcdn.com/w320/mw.png", true, -13.5, 34, 1467},
	{"dosyalar/bayraklar/irak.png", "Irak", "Iraq", "Irak", "Baghdad", "Asia", "https://flagcdn.com/w320/iq.png", true, 33, 44, 789},
	{"dosyalar/bayraklar/svalbardvejanmayen.png", "Svalbardvejanmayen", "Svalbardandjanmayen", "Svalbardvejanmayen", "Longyearbyen", "Europe", "https://flagcdn.com/w320/sj.png", false, 78, 20, 323},
	{"dosyalar/bayraklar/benin.png", "Benin", "Benin", "Benin", "Portonovo", "Africa", "https://flagcdn.com/w320/bj.png", true, 9.5, 2.25, 176},
	{"dosyalar/bayraklar/japonya.png", "Japonya", "Japan", "Japonya", "Tokyo", "Asia", "https://flagcdn.com/w320/jp.png", true, 36, 138, 932},
	{"dosyalar/bayraklar/dominikcumhuriyeti.png", "Dominikcumhuriyeti", "Dominicanrepublic", "Dominikcumhuriyeti", "Santodomingo", "Americas", "https://flagcdn.com/w320/do.png", true, 19, -70.67, 1658},
	{"dosyalar/bayraklar/katar.png", "Katar", "Qatar", "Katar", "Doha", "Asia", "https://flagcdn.com/w320/qa.png", true, 25.5, 51.25, 336},
	{"dosyalar/bayraklar/gabon.png", "Gabon", "Gabon", "Gabon", "Libreville", "Africa", "https://flagcdn.com/w320/ga.png", true, -1, 11.75, 161 } };
//------------------------------------------------------------------------------------------------------------------------- fonksiyonlar
void download(const string& url, const string& file, const bool& kesinlik, const int& dosyaboyut) {
	create_directories(path(file).parent_path());
	if (kesinlik || (!exists(file)) || (dosyaboyut != 0 && dosyaboyut != file_size(file))) 
		system(("powershell -Command \"Invoke-WebRequest -Uri '" + url + "' -OutFile '" + file + "'\"").c_str());
}
double mesafehesapla(const double& latitude1, const double& longitude1, const double& latitude2, const double& longitude2) {
	const double PI = 3.14159265358979323846264338327950288;
	double theta = longitude1 - longitude2;
	double distance = acos(sin(latitude1 * PI / 180.0) * sin(latitude2 * PI / 180.0) +
		cos(latitude1 * PI / 180.0) * cos(latitude2 * PI / 180.0) * cos(theta * PI / 180.0)) * 180.0 / PI;
	distance *= 60 * 1.1515 * 1.609344;
	return round(distance);
}
string harfcevir(const string& input) {
	vector<pair<char, char>> turkceToIngilizce = {
	  {'ç', 'c'}, {'Ç', 'C'}, {'ğ', 'g'}, {'Ğ', 'G'}, {'ı', 'i'}, {'İ', 'I'},
	  {'ö', 'o'}, {'Ö', 'O'}, {'ş', 's'}, {'Ş', 'S'}, {'ü', 'u'}, {'Ü', 'U'},
	  {'', 'g'}, {'1', 'i'}, {'_', 's'}
	};
	string result;
	for (char ch : input) {
		auto it = find_if(turkceToIngilizce.begin(), turkceToIngilizce.end(),
			[&ch](const pair<char, char>& p) { return p.first == ch; });

		if (it != turkceToIngilizce.end()) {
			result += it->second;
		}
		else {
			result += ch;
		}
	}
	return result;
}
string Pusula(double lat1, double lon1, double lat2, double lon2) {
	const double PI = 3.14159265358979323846264338327950288;
	lat1 *= PI / 180.0;
	lon1 *= PI / 180.0;
	lat2 *= PI / 180.0;
	lon2 *= PI / 180.0;
	double brng = fmod(atan2(sin(lon2 - lon1) * cos(lat2), cos(lat1) * sin(lat2) - sin(lat1) * cos(lat2) * cos(lon2 - lon1)) * 180 / PI + 360, 360);
	const char* yonler[] = { "Kuzey", "Kuzeydogu", "Dogu", "Guneydogu", "Guney", "Guneybati", "Bati", "Kuzeybati" };
	return (brng < 0 || brng >= 360) ? "Geçersiz derece değeri" : yonler[static_cast<int>((brng + 22.5) / 45.0) % 8];
}
string kelimeDuzelt(const string& kelime) {
	string sonuc;
	for (char karakter : kelime) {
		if (isalpha(karakter))
			sonuc += (sonuc.empty()) ? toupper(karakter) : tolower(karakter);
	}
	return sonuc;
}
string bulunanBenzerUlke(const string& komut) {
	int en_yuksek_benzerlik = 0;
	string en_benzer_ulke;
	string duzeltilmis_komut = kelimeDuzelt(komut);
	for (const auto& ulke : ulke) {
		const string& ulke_isim = ulke.isim;
		const string& ulke_trisim = ulke.trisim;
		const string& ulke_enisim = ulke.enisim;
		auto benzerlik = [&](const string& ulke_ad) {
			int benzerlik_degeri = 0;
			for (size_t i = 0; i < duzeltilmis_komut.size(); ++i) {
				if (i < ulke_ad.size() && tolower(duzeltilmis_komut[i]) == tolower(ulke_ad[i]))  benzerlik_degeri++;
				else break;
			}
			return benzerlik_degeri;
			};

		int benzerlik_toplam = benzerlik(ulke_isim) + benzerlik(ulke_trisim) + benzerlik(ulke_enisim);
		if (benzerlik_toplam > en_yuksek_benzerlik) {
			en_yuksek_benzerlik = benzerlik_toplam;
			en_benzer_ulke = ulke_isim;
		}
	}
	if (duzeltilmis_komut == "Pas" || duzeltilmis_komut == "Bitir" || duzeltilmis_komut == "Kapat" || duzeltilmis_komut == "Ayarlar" || duzeltilmis_komut == "Temizle") 
		return duzeltilmis_komut;
	return en_benzer_ulke;
}
//------------------------------------------------------------------------------------------------------------------------- açılan pencereler
void endGameMenu(RenderWindow& window, Event& event, Text& menuText, Sprite& sprite, bool& oyun, int winstreak, int toplampuan) {
	string yazilanlar = "Oyun Bitti\tYapan Kerem Kuyucu\n";
	yazilanlar += "Dogru Sayiniz: " + to_string(winstreak) + "\n";
	yazilanlar += "Puaniniz: " + to_string(toplampuan) + "\n";
	menuText.setCharacterSize(40); menuText.setFillColor(Color::Red); menuText.setString(yazilanlar);
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				oyun = false;
				break;
			}
		}
		window.clear(Color(30, 30, 30));
		window.draw(sprite2);
		window.draw(menuText);
		window.display();
	}
}
void ulkekurallari() {
	ifstream dosya("dosyalar/ulkekurallari.txt"); dosya >> amerikakitasi >> asyakitasi >> afrikakitasi >> avrupakitasi >> okyanusyakitasi >> antartikakitasi >> bmuyeligi;
	vector<string> secenekler = { "Amerika Kitasi", "Asya Kitasi", "Afrika Kitasi", "Avrupa Kitasi", "Okyanusya Kitasi", "Antartika Kitasi", "Birlesmis Milletler Uyeligi", "Ayarlari Kapatmak Icin seciniz" };
	bool oyun = true;
	int secim = 0, a = 0;
	int ulkesayisi = 0;
	while (oyun) {
		RenderWindow window(VideoMode(800, 500), "GeoGame");
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					if (ulkesayisi < 10) {
						window.close();
						yanlis.play();
					}
					else {
						window.close();
						ofstream dosya("dosyalar/ulkekurallari.txt");  dosya << amerikakitasi << endl << asyakitasi << endl << afrikakitasi << endl << avrupakitasi << endl << okyanusyakitasi << endl << antartikakitasi << endl << bmuyeligi << endl;
						oyun = false;
						break;
					}
				}
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Left) {
						secim--;
						if (secim < 0) secim = static_cast<int>(secenekler.size()) - 1;
					}
					else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::Right) {
						secim++;
						if (secim >= secenekler.size()) secim = 0;
					}
					else if (event.key.code == Keyboard::Return) {
						window.close();
						switch (secim) {
						case 0: amerikakitasi = !amerikakitasi; break;
						case 1: asyakitasi = !asyakitasi; break;
						case 2: afrikakitasi = !afrikakitasi; break;
						case 3: avrupakitasi = !avrupakitasi; break;
						case 4: okyanusyakitasi = !okyanusyakitasi; break;
						case 5: antartikakitasi = !antartikakitasi; break;
						case 6: bmuyeligi = !bmuyeligi; break;
						case 7:
							if (ulkesayisi < 10) {
								yanlis.play();
							}
							else {
								window.close();
								ofstream dosya("dosyalar/ulkekurallari.txt");  dosya << amerikakitasi << endl << asyakitasi << endl << afrikakitasi << endl << avrupakitasi << endl << okyanusyakitasi << endl << antartikakitasi << endl << bmuyeligi << endl;
								oyun = false;
								break;
							}
						}
					}
					if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num8)
						secim = event.key.code - Keyboard::Num1;
				}
			}
			window.clear(Color(30, 30, 30)); // Arka plan rengi
			ulkesayisi = 0;
			for (int i = 0; i < ulke.size(); i++) {
				if (((amerikakitasi && ulke[i].kita == "Americas") ||
					(asyakitasi && ulke[i].kita == "Asia") ||
					(afrikakitasi && ulke[i].kita == "Africa") ||
					(avrupakitasi && ulke[i].kita == "Europe") ||
					(okyanusyakitasi && ulke[i].kita == "Oceania") ||
					(antartikakitasi && ulke[i].kita == "Antarctic")
					) && (bmuyeligi ? true : ulke[i].bm))
				{
					ulkesayisi++;
				}
			}
			menuText.setString(ulkesayisi < 10 ? "Secilen ulke sayisi 10 dan az olamaz." : "Ayarlar ----(Sari ise aktiftir)---->");
			if (ulkesayisi < 10) {
				menuText.setFillColor(Color(255, 165, 0));
			}
			else {
				menuText.setFillColor(Color::Blue);
			}
			menuText.setPosition(10, 0); // adjust position as needed
			window.draw(menuText);
			menuText.setString("Seçeneklere Uyan Ulke Sayisi: " + to_string(ulkesayisi));
			menuText.setFillColor(Color::Magenta);
			menuText.setPosition(10, 50); // adjust position as needed
			window.draw(menuText);
			vector<bool> kurallar = { amerikakitasi, asyakitasi, afrikakitasi, avrupakitasi, okyanusyakitasi, antartikakitasi, bmuyeligi };
			for (int i = 0; i < secenekler.size(); ++i) {
				menuText.setString(((secim == i) ? " >  " : "") + secenekler[i]);
				menuText.setPosition(10, 100 + static_cast<float>(i) * 50);
				if (i == secenekler.size() - 1)
					menuText.setFillColor(Color::White);
				else if (kurallar[i] == false)
					menuText.setFillColor(Color::Red);
				else
					menuText.setFillColor(Color::Green);
				window.draw(menuText);
			}
			menuText.setCharacterSize(40);
			window.display();
		}
	}
}
void secilenUlkeyiBelirle(string& kaliciyazilanlar, Ulkeler& kalici, Ulkeler& gecici) {
	ifstream dosya("dosyalar/ulkekurallari.txt"); dosya >> amerikakitasi >> asyakitasi >> afrikakitasi >> avrupakitasi >> okyanusyakitasi >> antartikakitasi >> bmuyeligi;
	bool gecicibilgi = false;
	int randomSayi = 0;
	do {
		randomSayi = rand() % ulke.size();
	} while (ulke[randomSayi].bilgi
		|| (!amerikakitasi && ulke[randomSayi].kita == "Americas")
		|| (!asyakitasi && ulke[randomSayi].kita == "Asia")
		|| (!afrikakitasi && ulke[randomSayi].kita == "Africa")
		|| (!avrupakitasi && ulke[randomSayi].kita == "Europe")
		|| (!okyanusyakitasi && ulke[randomSayi].kita == "Oceania")
		|| (!antartikakitasi && ulke[randomSayi].kita == "Antarctic")
		|| (!bmuyeligi && !ulke[randomSayi].bm));

	kalici = Ulkeler(ulke[randomSayi].bayrak, ulke[randomSayi].trisim, ulke[randomSayi].enisim, ulke[randomSayi].isim, ulke[randomSayi].baskent, ulke[randomSayi].kita, ulke[randomSayi].url, ulke[randomSayi].bm, ulke[randomSayi].enlem, ulke[randomSayi].boylam, ulke[randomSayi].dosyaboyut);
	gecici = Ulkeler("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
	ulke[randomSayi].bilgi = true;
	for (int i = 0; i < ulke.size(); i++) {
		if (ulke[i].bilgi
			|| (!amerikakitasi && ulke[i].kita == "Americas")
			|| (!asyakitasi && ulke[i].kita == "Asia")
			|| (!afrikakitasi && ulke[i].kita == "Africa")
			|| (!avrupakitasi && ulke[i].kita == "Europe")
			|| (!okyanusyakitasi && ulke[i].kita == "Oceania")
			|| (!antartikakitasi && ulke[i].kita == "Antarctic")
			|| (!bmuyeligi && !ulke[i].bm))
		{
		}
		else {
			gecicibilgi = true;
			break;
		}
	}
	if (gecicibilgi == false) {
		for (int i = 0; i < ulke.size(); i++)
			ulke[i].bilgi = false;
		kaliciyazilanlar += "Tüm ülkeler bir kere seçildi, tüm ülkeler tekrar seçiliyor.\n";
	}
	download(ulke[randomSayi].url, ulke[randomSayi].bayrak, 0, ulke[randomSayi].dosyaboyut);
}
void ulkegirisi(RenderWindow& window, Event& event, Text& menuText, Sprite& sprite, Sprite& sprite2, string& komut, string& kaliciyazilanlar, string& yazilanlar) {
	srand(static_cast<unsigned int>(time(0)));
	window.clear(Color(30, 30, 30));
	komut = "";
	sprite2.setPosition(10, 200);
	menuText.setString(kaliciyazilanlar + yazilanlar + "Lütfen bir tahmin girin: " + komut + "\nSunumu demek istediniz (evet ise tab veya ctrl tusuna basiniz) : " + bulunanBenzerUlke(komut));
	window.draw(sprite);
	window.draw(sprite2);
	window.draw(menuText);
	window.display();

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
				komut = "kapat";
				break;
			}
			if (event.type == Event::TextEntered) {
				if (event.text.unicode == '\r') { // Enter tuşuna basıldıysa
					window.close();
					break;
				}
				else if (event.text.unicode == '\b') { // Silme tuşuna basıldıysa
					if (!komut.empty()) {
						komut.pop_back();
						menuText.setString(kaliciyazilanlar + yazilanlar + "Lütfen bir tahmin girin: " + komut + "\nSunumu demek istediniz (evet ise tab veya ctrl tusuna basiniz) : " + bulunanBenzerUlke(komut));
						window.clear(Color(30, 30, 30));
						window.draw(sprite);
						window.draw(sprite2);
						window.draw(menuText);
						window.display();
					}
				}
				else {
					// ASCII ve Türkçe karakterleri kontrol et
					if ((event.text.unicode >= 32 && event.text.unicode <= 126) ||
						(event.text.unicode >= 0x00C0 && event.text.unicode <= 0x017F) ||
						(event.text.unicode >= 0x011E && event.text.unicode <= 0x0130) ||
						(event.text.unicode == 0x015E) || (event.text.unicode == 0x015F) ||
						(event.text.unicode == 0x011F) || (event.text.unicode == 0x0131) ||
						(event.text.unicode == 0x00FC) || (event.text.unicode == 0x00DC) ||
						(event.text.unicode == 0x00F6) || (event.text.unicode == 0x00D6) ||
						(event.text.unicode == 0x00E7) || (event.text.unicode == 0x00C7)) {

						komut += static_cast<char>(event.text.unicode);
						komut = harfcevir(komut);
						menuText.setString(kaliciyazilanlar + yazilanlar + "Lütfen bir tahmin girin: " + komut + "\nSunumu demek istediniz (evet ise tab veya ctrl tusuna basiniz) : " + bulunanBenzerUlke(komut));
						window.clear(Color(30, 30, 30));
						window.draw(sprite);
						window.draw(sprite2);
						window.draw(menuText);
						window.display();
					}
				}
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Tab) { // Tab tuşuna basıldıysa
				komut = bulunanBenzerUlke(komut);
				window.close();
				break;
			}
			if (window.hasFocus())
				break;
		}
	}
	ofstream dosyaYaz("dosya.txt");
	dosyaYaz << komut;
	dosyaYaz.close();
}
void bilgimenu(RenderWindow& window, Event& event, Text& menuText, Sprite& sprite, bool& oyun, Music& yenitur, vector<string>& secilen) {
	window.clear(Color(30, 30, 30));
	menuText.setString(secilen[0] + "\n" + secilen[1] + "\n" + secilen[2] + "\n" + secilen[3] + "\n" + secilen[4] + "\n" + secilen[5] + "\n" + secilen[6] + "\n");
	window.draw(sprite);
	window.draw(menuText);
	window.display();
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == Event::TextEntered && event.text.unicode < 128) {
				if (event.text.unicode == '\r') { // Enter tuşuna basıldıysa
					window.close();
					oyun = true;
					yenitur.play();
					break;
				}
			}
			if (event.type == Event::Closed)
				window.close();
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------- mesafe oyun
void Mesafe() {
	RenderWindow window(VideoMode(1920, 1080), "GeoGame");
	menuText.setCharacterSize(35);
	menuText.setFillColor(Color::Black);
	Sprite sprite(arkaplan);
	bool oyun = false;
	int winstreak = 0, toplampuan = 0, puan = 0, joker = 3;
	string secilen[7] = { "Mesafeden Ulke Bilme Oyunu","Mesafeden ulke bilme oyununa hos geldiniz. \nAmaciniz, 250 ülkeden rastgele secilen bir ulkeyi bilmek.\nMesafeler +-100 Km fark olabilir.\nKonum olarak ülkelerin tam ortalari baz alinmistir.",
		"Tahminleri yazarken turkce harfleri gostermiyor bu yuzden harf eksik kaldi diye onemsemeyin tahminizi etkilemeyecektir.",
		"Puan Sistemi: Her turda puaniniz 100 den baslar her yanlis tahminde 10 puan azalir.\n8 Tahminden sonra kazanilan puan 20'e sabitlenir tur bitince tekrar 100'den baslar.",
		"Ulkeyi gecmek icin Pas yazin\nOyunu kapatmak icin 'Kapat' yazin.\nAyarlari duzenlemek icin Ayarlar yazin, sonraki turda etki eder.",
		"Baslamak icin 'Enter' tusuna basin oyunu bitirmek icin ise 'Bitir' yazin.","Eger ekrandaki yaziler guzukmemeye basladi ise temizle yaziniz." };
	vector<string> secilenVector(secilen, secilen + 7);
	bilgimenu(window, event, menuText, sprite, oyun, yenitur, secilenVector);
	while (oyun) {
		Ulkeler kalici("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
		Ulkeler gecici("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
		kaliciyazilanlar = "";
		secilenUlkeyiBelirle(kaliciyazilanlar, kalici, gecici);
		puan = 110;
		while (true) {
			RenderWindow window(VideoMode(1920, 1080), "GeoGame");
			ulkegirisi(window, event, menuText, sprite, sprite2, komut, kaliciyazilanlar, yazilanlar);
			yazilanlar = "";
			komut = kelimeDuzelt(komut);
			for (size_t a = 0;a < (ulke.size());a++) {
				if (ulke[a].ks(komut)) {
					gecici = Ulkeler(ulke[a].bayrak, ulke[a].trisim, ulke[a].enisim, ulke[a].isim, ulke[a].baskent, ulke[a].kita, ulke[a].url, ulke[a].bm, ulke[a].enlem, ulke[a].boylam, ulke[a].dosyaboyut);
					puan -= 10;
					break;
				}
			}
			if (komut == "Kapat") {
				oyun = 0;
				break;
			}
			if (komut == "Bitir") {
				RenderWindow window(VideoMode(1920, 1080), "GeoGame");
				endGameMenu(window, event, menuText, sprite, oyun, winstreak, toplampuan);
				komut = "Kapat";
				break;
			}
			if (komut == "Joker") {
				if (joker > 0) {
					joker -= 1;
					yazilanlar += "Ulkenin Baskenti: " + kalici.baskent + "  ";
					yazilanlar += to_string(joker) + " Joker hakkiniz kaldi.\n";
					puan -= 25;
				}
				else
					yazilanlar += to_string(joker) + "Joker hakkiniz bitmiştir.\n";
			}
			else if (komut == "Pas") {
				yenitur.play();
				kaliciyazilanlar = "";
				yazilanlar += "Gecilen Ulke: " + kalici.isim + "  ";
				yazilanlar += "Kordinati Enlem: " + to_string(kalici.enlem) + " Boylam: " + to_string(kalici.boylam) + "\n";
				break;
			}
			else if (komut == "Temizle")
				kaliciyazilanlar = "";
			else if (komut == "Ayarlar")
				ulkekurallari();
			else if (gecici.isim == kalici.isim) {
				dogru.play();
				kaliciyazilanlar = "";
				yazilanlar += "Dogru ulkeyi buldun Tebrikler!!\n";
				toplampuan += (puan < 20 ? 20 : puan);
				winstreak++;
				break;
			}
			else if (gecici.ks(komut)) {
				yanlis.play();
				komut = to_string(mesafehesapla(gecici.enlem, gecici.boylam, kalici.enlem, kalici.boylam));
				komut.erase(komut.size() - 7);
				kaliciyazilanlar += "Tahmin: " + gecici.isim + "  ";
				kaliciyazilanlar += "Mesafe: " + komut + " kilometre  ";
				kaliciyazilanlar += "Yön: " + Pusula(gecici.enlem, gecici.boylam, kalici.enlem, kalici.boylam) + "\n";
			}
			else if (!gecici.ks(kalici.isim)) {
				yanlis.play();
				yazilanlar += "Boyle bir ulke bulunamadi.\n";
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------- bayrak oyun
void Bayrak() {
	RenderWindow window(VideoMode(1920, 1080), "GeoGame");
	menuText.setCharacterSize(35);
	menuText.setFillColor(Color::Black);
	Sprite sprite(arkaplan);
	bool oyun = false;
	int winstreak = 0, toplampuan = 0, puan = 0;
	string secilen[7] = { "Bayrak Bilme Oyunu", "Bayrak Bilme Oyununa hos geldiniz. ", "Amaciniz, 250 ulkeden rastgele secilen bir ulkenin bayragini bilmek.",
		"Tahminleri yazarken turkce harfleri gostermiyor bu yuzden harf eksik kaldi diye onemsemeyin tahminizi etkilemeyecektir.",
		"Puan Sistemi: Her turda puaniniz 50 den baslar her yanlis tahminde 10 puan azalir.\n3 Tahminden sonra kazanilan puan 20'e sabitlenir tur bitince tekrar 50'den baslar.",
		"Ulkeyi gecmek icin Pas yazin\nOyunu kapatmak icin 'Kapat' yazin.\nAyarlari duzenlemek icin Ayarlar yazin, sonraki turda etki eder.",
		"Baslamak icin 'Enter' tusuna basin oyunu bitirmek icin ise 'Bitir' yazin." };
	vector<string> secilenVector(secilen, secilen + 7);
	bilgimenu(window, event, menuText, sprite, oyun, yenitur, secilenVector);
	while (oyun) {
		Ulkeler kalici("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
		Ulkeler gecici("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
		kaliciyazilanlar = "";
		secilenUlkeyiBelirle(kaliciyazilanlar, kalici, gecici);
		puan = 50;
		while (true) {
			menuText.setFillColor(Color::Yellow);
			RenderWindow window(VideoMode(1920, 1080), "GeoGame");
			bayrak.loadFromFile(kalici.bayrak);
			Sprite sprite2(bayrak);
			ulkegirisi(window, event, menuText, sprite, sprite2, komut, kaliciyazilanlar, yazilanlar);
			komut = kelimeDuzelt(komut);
			for (size_t a = 0;a < (ulke.size());a++) {
				if (ulke[a].ks(komut)) {
					gecici = Ulkeler(ulke[a].bayrak, ulke[a].trisim, ulke[a].enisim, ulke[a].isim, ulke[a].baskent, ulke[a].kita, ulke[a].url, ulke[a].bm, ulke[a].enlem, ulke[a].boylam, ulke[a].dosyaboyut);
					break; 
				}
			}
			if (komut == "Kapat") {
				oyun = 0;
				break;
			}
			if (komut == "Bitir") {
				RenderWindow window(VideoMode(1920, 1080), "GeoGame");
				endGameMenu(window, event, menuText, sprite, oyun, winstreak, toplampuan);
				komut = "Kapat";
				break;
			}
			if (komut != "Pas" && komut != "Bitir" && !gecici.ks(kalici.isim)) {
				yanlis.play();
				yazilanlar = "Boyle bir ulke bulunamadi. Yazilan komut: " + komut + "\n";
			}
			if (gecici.isim == kalici.isim) {
				dogru.play();
				yazilanlar = "Dogru ulkeyi buldun Tebrikler!!\n";
				kaliciyazilanlar = "";
				toplampuan += (puan < 20 ? 20 : puan);
				winstreak++;
				break;
			}
			if (gecici.ks(komut)) {
				yanlis.play();
				yazilanlar = "Yanlis tahmin!!\n";
				puan -= 10;
			}
			if (komut == "Ayarlar")
				ulkekurallari();
			if (komut == "Pas") {
				yenitur.play();
				kaliciyazilanlar = "";
				yazilanlar = "Geçilen Ülke: " + kalici.isim + "\n";
				break;
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------- baskent oyun
void Baskent() {
	RenderWindow window(VideoMode(1920, 1080), "GeoGame");
	menuText.setCharacterSize(35);
	menuText.setFillColor(Color::Black);
	Sprite sprite(arkaplan);
	bool oyun = false;
	int winstreak = 0, toplampuan = 0, puan = 0;
	string secilen[7] = { "Baskent Bilme Oyunu","Baskent Bilme Oyununa hos geldiniz. \nAmaciniz 250 ulkeden rastgele secilen bir ulkenin baskentini bilmek.",
		"Tahminleri yazarken turkce harfleri gostermiyor bu yuzden harf eksik kaldi diye onemsemeyin tahminizi etkilemeyecektir.",
		"Puan Sistemi: Her turda puaniniz 50 den baslar her yanlis tahminde 10 puan azalir.\n3 Tahminden sonra kazanilan puan 20'e sabitlenir tur bitince tekrar 50'den baslar.",
		"Ulkeyi gecmek icin Pas yazin","Oyunu kapatmak icin 'Kapat' yazin.\nAyarlari duzenlemek icin Ayarlar yazin, sonraki turda etki eder.",
		"Baslamak icin 'Enter' tusuna basin oyunu bitirmek icin ise 'Bitir' yazin." };
	vector<string> secilenVector(secilen, secilen + 7);
	bilgimenu(window, event, menuText, sprite, oyun, yenitur, secilenVector);
	while (oyun) {
		Ulkeler kalici("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
		Ulkeler gecici("a", "a", "a", "a", "a", "a", "a", 0, 0, 0, 0);
		kaliciyazilanlar = "";
		secilenUlkeyiBelirle(kaliciyazilanlar, kalici, gecici);
		puan = 50;
		while (true) {
			RenderWindow window(VideoMode(1920, 1080), "GeoGame");
			yazilanlar += "Baskent Adi: " + kalici.baskent + "\n";
			ulkegirisi(window, event, menuText, sprite, sprite2, komut, kaliciyazilanlar, yazilanlar);
			komut = kelimeDuzelt(komut);
			for (size_t a = 0;a < (ulke.size());a++) {
				const Ulkeler& secilenulke = ulke[a];
				if (ulke[a].ks(komut)) {
					gecici = Ulkeler(ulke[a].bayrak, ulke[a].trisim, ulke[a].enisim, ulke[a].isim, ulke[a].baskent, ulke[a].kita, ulke[a].url, ulke[a].bm, ulke[a].enlem, ulke[a].boylam, ulke[a].dosyaboyut);
					break;
				}
			}
			if (komut == "Kapat") {
				oyun = 0;
				break;
			}
			if (komut == "Bitir") {
				RenderWindow window(VideoMode(1920, 1080), "GeoGame");
				endGameMenu(window, event, menuText, sprite, oyun, winstreak, toplampuan);
				komut = "Kapat";
				break;
			}
			if (kalici.ks(gecici.isim) || kalici.ks(gecici.trisim) || kalici.ks(gecici.enisim)) {
				dogru.play();
				yazilanlar = "Dogru ulkeyi buldun Tebrikler!!\n";
				kaliciyazilanlar = "";
				toplampuan += (puan < 20 ? 20 : puan);
				winstreak++;
				break;
			}
			else if (komut != "Pas" && komut != "Bitir" && komut != "Ayarlar") {
				yanlis.play();
				yazilanlar = "Boyle bir ulke bulunamadi.\n";
			}
			if (gecici.ks(komut)) {
				yanlis.play();
				yazilanlar = "Yanlis tahmin\n";
				puan -= 10;
			}
			if (komut == "Ayarlar")
				ulkekurallari();
			if (komut == "Pas") {
				yenitur.play();
				kaliciyazilanlar = "";
				yazilanlar = "Gecilen Ulke: " + kalici.isim + "\n";
				break;
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------------------- main bölüm
int main() {
	srand(static_cast<unsigned int>(time(0)));
	if (!font.loadFromFile("dosyalar/arial.ttf")) { download("https://drive.usercontent.google.com/download?id=1uJAWWTlFir4tJ4sZ5EPzmG8Snd2A-7bf", "dosyalar\\arial.ttf", 0, 915212); };
	if (!arkaplan.loadFromFile("dosyalar/arkaplan.png")) { download("https://drive.usercontent.google.com/download?id=1RDknWZSI6vPpCqL5NvCPohnWTG9T2_mW", "dosyalar\\arkaplan.png", 0, 66286); };
	if (!dogru.openFromFile("dosyalar/sesler/dogru.ogg")) { download("https://drive.usercontent.google.com/download?id=14QeyRRW8J2sZvGFQMmyY-Gjj6qavEa3J", "dosyalar\\sesler\\dogru.ogg", 0, 7703); }
	else 	dogru.setVolume(45);
	if (!yanlis.openFromFile("dosyalar/sesler/yanlis.ogg")) { download("https://drive.usercontent.google.com/download?id=1lfBSgz9ja7oSyLb3XQBbbMLDm_vzchRg", "dosyalar\\sesler\\yanlis.ogg", 0, 10769); }
	else 	yanlis.setVolume(45);
	if (!yenitur.openFromFile("dosyalar/sesler/yenitur.ogg")) { download("https://drive.usercontent.google.com/download?id=1M4JCY_AFmVbnWNn24Zbnq5rIfd3zR3zZ", "dosyalar\\sesler\\yenitur.ogg", 0, 23217); }
	else 	yenitur.setVolume(45);
	if (!arkafon.openFromFile("dosyalar/sesler/arkafon.ogg")) { download("https://drive.usercontent.google.com/download?id=1dq1MNEWyxkRsLug0v3qsb4lGPNHU_yir", "dosyalar\\sesler\\arkafon.ogg", 0, 1396954); }
	else { arkafon.setVolume(2); arkafon.setLoop(true); }
	Sprite sprite(arkaplan);
	vector<string> secenekler = { "1. Baskent Bilme Oyunu", "2. Mesafeden Ulke Bilme Oyunu", "3. Bayrak Bilme Oyunu", "4. Ulke Secim Ayarlari", "5. Muzik " };
	bool oyun = true;
	int secim = 0;
	while (oyun) {
		arkafonsarki ? arkafon.play() : arkafon.stop();
		menuText.setPosition(10, 10);
		RenderWindow window(VideoMode(1920, 1080), "GeoGame");
		while (window.isOpen()) {
			while (window.pollEvent(event)) {
				if (event.type == Event::Closed) {
					window.close(); oyun = false;
				}
				if (event.type == Event::KeyPressed) {
					if (event.key.code == Keyboard::Up || event.key.code == Keyboard::Left) {
						secim--;
						if (secim < 0) secim = static_cast<int>(secenekler.size()) - 1;
					}
					else if (event.key.code == Keyboard::Down || event.key.code == Keyboard::Right) {
						secim++;
						if (secim >= secenekler.size()) secim = 0;
					}
					else if (event.key.code == Keyboard::Return) {
						yenitur.play();
						window.close();
						switch (secim) {
						case 0: Baskent(); break;
						case 1: Mesafe(); break;
						case 2: Bayrak(); break;
						case 3: ulkekurallari(); break;
						case 4: arkafonsarki = !arkafonsarki; break;
						}
					}
					if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num8) {
						secim = event.key.code - Keyboard::Num1;
					}
				}
			}
			window.clear(Color(30, 30, 30)); // Arka plan rengi
			window.draw(sprite);
			string menuMetni;
			int a = 0;
			for (int i = 0; i < secenekler.size(); ++i) {
				menuMetni += ((i == secim) ? " > " : "   ") + secenekler[i] + ((i != secenekler.size() - 1) ? "\n" : "");
				if (i == 4)
					menuMetni += string(arkafonsarki ? "Kapa" : "Ac");
				if (i == secim)
					a = i;
			}
			menuText.setString("\n\n" + menuMetni);
			menuText.setFillColor(Color::Black);
			menuText.setCharacterSize(40);
			window.draw(menuText);
			std::string menuString = "\n\n\n\n\n\n" + std::string((a == 4) ? " > " : "   ") + secenekler[4] + string(arkafonsarki ? "Kapa" : "Ac");
			menuText.setString(menuString);
			menuText.setFillColor(arkafonsarki ? Color::Yellow : Color::Red);
			menuText.setCharacterSize(40);
			window.draw(menuText);
			menuText.setString(string(2 + a, '\n') + " > " + secenekler[a] + (a == 4 ? (arkafonsarki ? "Kapa" : "Ac") : ""));
			menuText.setFillColor(Color::Blue);
			menuText.setCharacterSize(40);
			window.draw(menuText);
			menuText.setString("\tGeoGame");
			menuText.setFillColor(Color(255, 128, 128));
			menuText.setCharacterSize(75);
			window.draw(menuText);
			window.display();
		}
	}
	return 0;
}
