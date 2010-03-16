#include <iostream>

#include "boost/foreach.hpp"

#include "general/ShopDb.h"
#include "products/Contact.h"
#include "products/Products.h"
#include "products/ProductTypes.h"
#include "products/OrderHeaders.h"
#include "user/UserAccount.h"
#include "user/User.h"
#include "user/ActionGroup.h"
using namespace av;

class AVShopDbInstall
{
public:
    AVShopDbInstall()
    {

    }

    void install()
    {
        _createDatabase();
        _insertUsers();
        _insertIntoProductTypes();
        _insertIntoProducts();
    }

private:
    void _createDatabase()
    {
        soci::session &_session = *_shopDb.getSession();
        _session << "delete from UserAccount";        
        _session << "delete from OrderRow";
        _session << "delete from OrderHeader";
        _session << "delete from Product";
        _session << "delete from ProductType";
        _session << "delete from Contact";
    }

    void _insertUsers()
    {
        Contact contact("Daniel", "Lindh", "Amivono AB",
                        "Linnegatan 7", "126 51", "STOCKHOLM", "+46-73-626 54 49",
                        "daniel@cybercow.se", "www.cybercow.se");

        UserAccount userNewUser(*_shopDb.getSession(), "arlukin", "password", contact);
        userNewUser.save();
    }

    void _insertIntoProductTypes()
    {
        ProductTypes * productTypes = _shopDb.getProductTypes();
        productTypes->destroy();

        productTypes->push_back(ProductType("Startpaket"));
        productTypes->push_back(ProductType("Huvudkontroller"));
        productTypes->push_back(ProductType("Fjärrkontroller"));
        productTypes->push_back(ProductType("Tryckknappar"));
        productTypes->push_back(ProductType("Plugin moduler"));
        productTypes->push_back(ProductType("Insatser"));
        productTypes->push_back(ProductType("Strömbrytare"));
        productTypes->push_back(ProductType("Sensorer"));
        productTypes->push_back(ProductType("Värme"));
        productTypes->push_back(ProductType("Motorstyrning"));
        productTypes->push_back(ProductType("Programvara"));

        productTypes->save();
    }

    void _insertIntoProducts()
    {
        std::string veraDesc = "Vera från Mi Casa Verde<br/> <br/> Med Vera från etablerade Mi Casa Verde får du ett av marknadens absolut bästa och enklaste utbyggbara Z-Wave-hemautomationssystem. Du behöver inte ens installera någon mjukvara på din dator, och du kommer garanterat att kunna hantera systemet utan några som helst tekniska kunskaper utöver de som vem som helst har.<br/> <br/> Att komma igång med detta system är bland det lättare man kan gör. Plugga bara in din Vera och gàin på hemsidan findvera.com, inga koder att slå in, ingen mjukvara att installera. Det är verkligen precis så enkelt. Vera inkluderar också videos som visar allt den kan göra och exakt hur du gör det. Internetsäkerheten är ett starkt kort hos Vera trots dess enkelhet att installera. Du väljer bara användarnamn och lösenord, sedan skyddas dessa av samma system som skyddar dig när du utför banktransaktioner.<br/> <br/> Vera fungerar tillsammans med alla Z-Wave produkter, så som till exempel lampmoduler, väggfasta ljusswitchar, termostater, grenkontakter, alarmsensorer, garageöppnare och persienner.<br/> <br/> <b>Huvudområden:</b><br/> <b>Energi</b><br/> Beskär din elräkningar ned till 1/3 av din kostnad i dagsläget och spara samtidigt vår värdefulla miljö! Vera ser till att din belysning, dina apparater och ditt värme/kylningssystem är aktiva bara när det behövs. Den presenterar även klar och enkel information över var specifik energi har blivit förbrukad, i vilka rum, i vilken typ av apparater och vilken tid under dagen eller i veckan.  På så sätt är det bara att tala om för Vera vad du vill ändra med din energiförbrukning, och den fixar det åt dig. Alternativt genomför du förändringen på det gamla hederliga sättet att slå av strömbrytare eller rycka sladdar ur vägguttagen, huvudsaken är att du sparar pengar och miljö, och detta är Vera mer än villig att hjälpa dig med.<br/> <br/> <b>Säkerhet</b><br/> Det är bara att plugga in Veras superenkla trådlösa(batteridrivna) kameror och rörelsesensorer med alarmfunktion för att direkt i din mobiltelefon få veta om något oförutsett hänt eller en objuden gäst tagit sig in hemma hos dig. Du kan se om något händer eller har hänt i ditt hem antingen live från din webläsare på jobbet, sommarstugan eller var du än befinner dig, eller så kan du för bara 4$ i månaden lagra data från din övervakningskamera på Veras hemsida. Du kan vara säker på att ingen så kallad hackare kan spionera på dig, då säkerheten är lika god som vid online-transaktioner pàbankernas hemsidor.<br/> <br/> <b>Komfort och enkelhet</b><br/> Om du trodde att hemautomation måste vara svårt så kan vi meddela att du har haft fel. Med Vera kan även en nybörjare göra allt du kan förvänta dig med ett högklassigt hemautomationssystem.<br/> <br/> <b>Scener:</b><br/> Bara peka och klicka för att skapa scener, så som exempelvis ?Lämna hemmet för arbete? eller kanske något mer kreativt namn. Hur som helst, i detta specifika scenario kanske du släcker all hemmets belysning och vrider ned termostaten några grader. Eller varför inte en ?Titta på film?- scen som dimrar belysningen, vinklar persienner/drar för gardiner, och sätter på din TV och hembiosystem.<br/> <br/> <b>Händelser:</b><br/> Här ingår tillämpningar som ?när rörelsesensorn registrerar aktivitet, slå på denna lampa i 5 minuter?, eller ?sätt på utomhusbelysningen vid solnedgång? eller varför inte ?meddela mig om denna sensorn märker av rörelse (via internet eller mobiltelefon).<br/> <br/> <b>Meddelanden:</b><br/> Vera kan skicka dig SMS, email, eller ringa på din telefon vid speciella skeenden som du vill bli underrättad om. Till exempel om en rörelsesensor märker att någon befinner sig i rummet, eller om belysning fortfarande är på efter att alla lämnat huset.<br/> <br/> <b>Timer:</b><br/> Så som ?Stäng av inomhusbelysning klockan 8 på morgonen? eller ?Vrid ned termostaten ett visst antal grader på arbetsdagar vid klockan 10 på morgonen?<br/>";

        Products * products = _shopDb.getProducts();
        products->destroy();

        Contact metric("fredrik", "welander", "Metric AB", "", "", "", "",
                       "fredrik.welander@metric.se", "www.metric.se");
        metric.save(*_shopDb.getSession());

        Contact savenHitech("cheng-huei", "kuo", "Saven Hitech", "", "", "", "",
                            "cheng-huei.kuo@savenhitech.se", "www.hitech.se");
        savenHitech.save(*_shopDb.getSession());

        Contact qees("S", "H", "Qees aPs", "", "", "", "",
                     "sh@blandford.dk/sh@qees.eu", "www.qees.eu");
        qees.save(*_shopDb.getSession());

        Contact expressControls("Eric", "", "Express controls", "", "", "", "",
                                "eric@expresscontrols.com", "www.expresscontrols.com");
        expressControls.save(*_shopDb.getSession());

        Contact tricklestar("Thomas", "Joergensen", "Tricklestar", "", "", "", "",
                            "thomas.joergensen@tricklestar.com", "www.tricklestar.com");
        tricklestar.save(*_shopDb.getSession());

        Contact micasaverde("Kelsey", "", "Micasaverde", "", "", "", "",
                            "kelsey@micasaverde.com", "https://shop.micasaverde.com/");
        micasaverde.save(*_shopDb.getSession());

        Contact lscontrol("P", "N", "Lscontrol", "", "", "", "",
                          "pn@lscontrol.dk", "www.lscontrol.dk");
        lscontrol.save(*_shopDb.getSession());

        Contact aeonLabs("P", "N", "Aeon labs", "", "", "", "",
                         "wli@aeon-labs.com", "www.aeon-labs.com");
        aeonLabs.save(*_shopDb.getSession());

        Contact mobileworld("Ville", "Partanen", "Mobileworld",
                        "", "", "", "",
                        "Ville.Partanen@mobileworld.fi", "www.obileworld.fi");
        mobileworld.save(*_shopDb.getSession());

        Contact actSolutions("", "", "Act-solutions",
                        "", "", "", "",
                        "daniel@cybercow.se", "http://www.act-solutions.com/HomePro/HomeProProductGrid.htm#Euro");
        actSolutions.save(*_shopDb.getSession());

        std::string description = "";
        products->push_back(Product("15\" Celeron touch computer",   description, metric,   metric,   "15A1",            "TC100", 0,  0,   ProductType("TouchComputer"),     Money(11000, "SEK"), Money(11000, "SEK")));
        products->push_back(Product("x\" touch computer",            description, savenHitech, savenHitech, "GOT-5840TL",      "TC101", 1,  4,   ProductType("TouchComputer"),     Money(5679, "SEK"),  Money(5679, "SEK")));
        products->push_back(Product("x\" touch computer",            description, savenHitech, savenHitech, "GOT-5100TL",      "TC102", 1,  4,   ProductType("TouchComputer"),     Money(5939, "SEK"),  Money(5939, "SEK")));
        products->push_back(Product("x\" touch computer",            description, savenHitech, savenHitech, "GOT-5120TL",      "TC103", 1,  4,   ProductType("TouchComputer"),     Money(6149, "SEK"),  Money(6149, "SEK")));
        products->push_back(Product("QEES-Ring (acc) eu",            description, qees, qees, "0100002",         "RM104", 20, 4,   ProductType("Remote"),            Money(34.00, "USD"), Money(34.00, "USD")));
        products->push_back(Product("QEES-Ring (s) eu",              description, qees, qees, "0101002",         "RM105", 20, 4,   ProductType("Remote"),            Money(34.00, "USD"), Money(34.00, "USD")));
        products->push_back(Product("QEES Wall (acc) eu",            description, qees, qees, "0200002",         "WS106", 20, 4,   ProductType("Wall Switch Button"),Money(39.00, "USD"), Money(39.00, "USD")));
        products->push_back(Product("QEES Wall (s) eu",              description, qees, qees, "0201002",         "WS107", 20, 4,   ProductType("Wall Switch Button"),Money(39.00, "USD"), Money(39.00, "USD")));
        products->push_back(Product("QEES Power eu",                 description, qees, qees, "0300002",         "WS108", 20, 4,   ProductType("Wall Switch Button"),Money(44.00, "USD"), Money(44.00, "USD")));
        products->push_back(Product("QEES Dimmer eu",                description, qees, qees, "0400002",         "WD109", 20, 6,   ProductType("Wall Dimmer Button"),Money(44.00, "USD"), Money(44.00, "USD")));
        products->push_back(Product("QEES Remote (acc) eu",          description, qees, qees, "0500002",         "RM110", 20, 8,   ProductType("Remote"),            Money(62.00, "USD"), Money(62.00, "USD")));
        products->push_back(Product("QEES Remote (s) eu",            description, qees, qees, "0501002",         "RM111", 20, 8,   ProductType("Remote"),            Money(62.00, "USD"), Money(62.00, "USD")));
        products->push_back(Product("QEES Master eu",                description, qees, qees, "1000002",         "CC112", 10, 8,   ProductType("Control Center"),    Money(17.00, "USD"), Money(17.00, "USD")));
        products->push_back(Product("EZMotion us",                   description, expressControls, expressControls, "EZM-US",          "SE113", 1,  1,   ProductType("Sensor"),            Money(90, "USD"),    Money(90, "USD")));
        products->push_back(Product("EZMotion eu",                   description, expressControls, expressControls, "EZM-EU",          "SE114", 1,  1,   ProductType("Sensor"),            Money(104, "USD"),   Money(104, "USD")));
        products->push_back(Product("EZMotion au/nz",                description, expressControls, expressControls, "EZM-AUNZ",        "SE115", 1,  1,   ProductType("Sensor"),            Money(104, "USD"),   Money(104, "USD")));
        products->push_back(Product("EU Z-Wave USB Stick",           description, tricklestar, tricklestar, "200ZW",           "ZD116", 1,  1,   ProductType("Z-wave Dongle"),     Money(19, "USD"),    Money(19, "USD")));
        products->push_back(Product("EU Z-Wave Remote",              description, tricklestar, tricklestar, "300ZW",           "RM117", 1,  1,   ProductType("Remote"),            Money(29, "USD"),       Money(29, "USD")));
        products->push_back(Product("Vera",                          veraDesc,    micasaverde, micasaverde, "",                "CC118", 1,  2,   ProductType("Control Center"),    Money(194, "USD"),   Money(194, "USD")));
        products->push_back(Product("USB Z-Wave Dongle",             description, micasaverde, micasaverde, "",                "ZD119", 1,  1,   ProductType("Z-wave Dongle"),     Money(42, "USD"),    Money(42, "USD")));
        products->push_back(Product("Wireless turning knob",         description, lscontrol, lscontrol, "ES 861",          "SE120", 50, 2,   ProductType("Sensor"),            Money(29, "EUR"),    Money(29, "EUR")));
        products->push_back(Product("Humidity sensor ",              description, lscontrol, lscontrol, "ES 861",          "SE121", 50, 2,   ProductType("Sensor"),            Money(41, "EUR"),    Money(41, "EUR")));
        products->push_back(Product("Z-Wave temperature sensor",     description, lscontrol, lscontrol, "ES 861 ",         "SE122", 50, 2,   ProductType("Sensor"),            Money(27, "EUR"),    Money(27, "EUR")));
        products->push_back(Product("Minimote Black",                description, aeonLabs, aeonLabs, "DSA03202B-ZWEU",  "RM123", 1,  3.5, ProductType("Remote"),            Money(40, "USD"),    Money(40, "USD")));
        products->push_back(Product("Minimote White",                description, aeonLabs, aeonLabs, "DSA03202W-ZWEU",  "RM124", 1,  3.5, ProductType("Remote"),            Money(40, "USD"),    Money(40, "USD")));
        products->push_back(Product("Door/Window Sensor",            description, aeonLabs, aeonLabs, "DSB04100-ZWEU",   "SE125", 1,  3.5, ProductType("Sensor"),            Money(38, "USD"),    Money(38, "USD")));
        products->push_back(Product("Z-Stick Series 2",              description, aeonLabs, aeonLabs, "DSA02203-ZWEU",   "ZD126", 1,  3.5, ProductType("Z-wave Dongle"),     Money(37, "USD"),    Money(37, "USD")));
        products->push_back(Product("Z-Stick Lite",                  description, aeonLabs, aeonLabs, "DSA07203-ZWEU",   "ZD127", 1,  3.5, ProductType("Z-wave Dongle"),     Money(34, "USD"),    Money(34, "USD")));
        products->push_back(Product("Smart Energy Switch",           description, aeonLabs, aeonLabs, "DSC06xxx-ZWEU",   "SW128", 1,  3.5, ProductType("Switch"),            Money(41, "USD"),    Money(41, "USD")));
        products->push_back(Product("Smart Energy Illuminator",      description, aeonLabs, aeonLabs, "DSC08xxx-ZWEU",   "DI129", 1,  3.5, ProductType("Dimmer"),            Money(41, "USD"),    Money(41, "USD")));
        products->push_back(Product("Remote control",                                   description, actSolutions, mobileworld, "ZTH200", "RM130", 1, 2, ProductType("Remote"),              Money(53.24, "EUR"), Money(53.24, "EUR")));
        products->push_back(Product("300W Plug-in Dimmer Module (EU-Shuko)",            description, actSolutions, mobileworld, "ZDP200", "DI131", 1, 2, ProductType("Dimmer"),              Money(31.97, "EUR"), Money(31.97, "EUR")));
        products->push_back(Product("10A Plug-in Appliance Module (EU-Shuko)",          description, actSolutions, mobileworld, "ZRP200", "SW132", 1, 2, ProductType("Switch"),              Money(31.97, "EUR"), Money(31.97, "EUR")));
        products->push_back(Product("Wall Mount, Battery Powered PIR Sensor",           description, actSolutions, mobileworld, "ZIR010", "SE133", 1, 2, ProductType("Sensor"),              Money(56.12, "EUR"), Money(56.12, "EUR")));
        products->push_back(Product("Dimmer, Wall-mount, 230v, 500W",                   description, actSolutions, mobileworld, "ZDW232", "WD134", 1, 2, ProductType("Wall Dimmer Button"),  Money(46.58, "EUR"), Money(46.58, "EUR")));
        products->push_back(Product("Dimmer, Wall-mount, 230v, 500W,",                  description, actSolutions, mobileworld, "ZDW230", "WD135", 1, 2, ProductType("Wall Dimmer Button"),  Money(48.87, "EUR"), Money(48.87, "EUR")));
        products->push_back(Product("Dual Dimmer, Wall-mount, 230v, 500W,",             description, actSolutions, mobileworld, "ZDM230", "WD136", 1, 2, ProductType("Wall Dimmer Button"),  Money(48.87, "EUR"), Money(48.87, "EUR")));
        products->push_back(Product("Dual Relay, Wall-mount, 230v, 10A,",               description, actSolutions, mobileworld, "ZRM230", "WS137", 1, 2, ProductType("Wall Switch Button"),  Money(46.13, "EUR"), Money(46.13, "EUR")));
        products->push_back(Product("Relay, Wall-mount, 230v, 10A,",                    description, actSolutions, mobileworld, "ZRW230", "WS138", 1, 2, ProductType("Wall Switch Button"),  Money(42.02, "EUR"), Money(42.02, "EUR")));
        products->push_back(Product("Dual, Transmitter, Wall-mount, 230v, 2 rocker",    description, actSolutions, mobileworld, "ZTM230", "WS139", 1, 2, ProductType("Wall Switch Button"),  Money(45.67, "EUR"), Money(45.67, "EUR")));

        products->save();
    }   

private:
    ShopDb _shopDb;
};

int main(int argc, char **argv)
{
    AVShopDbInstall install;
    install.install();
}
