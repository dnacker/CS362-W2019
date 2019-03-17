import junit.framework.TestCase;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {

   /* from https://www.iana.org/assignments/uri-schemes/uri-schemes.xhtml
   *  They are not used here because the UrlValidator's whole scheme tester throws
   *  exceptions (even on the simple schemes below) and thus using all of these
   *  valid schemes is just a waste of resources. If the code were fixed these
   *  would likely prove useful... */
   // private static String[] schemes = {"aaa://", "aaas://", "about://", "acap://", "acct://", "acr://", "adiumxtra://", "afp://", "afs://", "aim://", "appdata://", "apt://", "attachment://", "aw://", "barion://", "beshare://", "bitcoin://", "bitcoincash://", "blob://", "bolo://", "browserext://", "calculator://", "callto://", "cap://", "chrome://", "chrome-extension://", "cid://", "coap://", "coap+tcp://", "coap+ws://", "coaps://", "coaps+tcp://", "coaps+ws://", "com-eventbrite-attendee://", "content://", "conti://", "crid://", "cvs://", "data://", "dav://", "diaspora://", "dict://", "did://", "dis://", "dlna-playcontainer://", "dlna-playsingle://", "dns://", "dntp://", "dpp://", "dtn://", "dvb://", "ed2k://", "elsi://", "example://", "facetime://", "fax://", "feed://", "feedready://", "file://", "filesystem://", "finger://", "fish://", "ftp://", "geo://", "gg://", "git://", "gizmoproject://", "go://", "gopher://", "graph://", "gtalk://", "h323://", "ham://", "hcap://", "hcp://", "http://", "https://", "hxxp://", "hxxps://", "hydrazone://", "iax://", "icap://", "icon://", "im://", "imap://", "info://", "iotdisco://", "ipn://", "ipp://", "ipps://", "irc://", "irc6://", "ircs://", "iris://", "iris.beep://", "iris.lwz://", "iris.xpc://", "iris.xpcs://", "isostore://", "itms://", "jabber://", "jar://", "jms://", "keyparc://", "lastfm://", "ldap://", "ldaps://", "leaptofrogans://", "lvlt://", "magnet://", "mailserver://", "mailto://", "maps://", "market://", "message://", "microsoft.windows.camera://", "microsoft.windows.camera.multipicker://", "microsoft.windows.camera.picker://", "mid://", "mms://", "modem://", "mongodb://", "moz://", "ms-access://", "ms-browser-extension://", "ms-calculator://", "ms-drive-to://", "ms-enrollment://", "ms-excel://", "ms-eyecontrolspeech://", "ms-gamebarservices://", "ms-gamingoverlay://", "ms-getoffice://", "ms-help://", "ms-infopath://", "ms-inputapp://", "ms-lockscreencomponent-config://", "ms-media-stream-id://", "ms-mixedrealitycapture://", "ms-mobileplans://", "ms-officeapp://", "ms-people://", "ms-project://", "ms-powerpoint://", "ms-publisher://", "ms-restoretabcompanion://", "ms-screenclip://", "ms-screensketch://", "ms-search://", "ms-search-repair://", "ms-secondary-screen-controller://", "ms-secondary-screen-setup://", "ms-settings://", "ms-settings-airplanemode://", "ms-settings-bluetooth://", "ms-settings-camera://", "ms-settings-cellular://", "ms-settings-cloudstorage://", "ms-settings-connectabledevices://", "ms-settings-displays-topology://", "ms-settings-emailandaccounts://", "ms-settings-language://", "ms-settings-location://", "ms-settings-lock://", "ms-settings-nfctransactions://", "ms-settings-notifications://", "ms-settings-power://", "ms-settings-privacy://", "ms-settings-proximity://", "ms-settings-screenrotation://", "ms-settings-wifi://", "ms-settings-workplace://", "ms-spd://", "ms-sttoverlay://", "ms-transit-to://", "ms-useractivityset://", "ms-virtualtouchpad://", "ms-visio://", "ms-walk-to://", "ms-whiteboard://", "ms-whiteboard-cmd://", "ms-word://", "msnim://", "msrp://", "msrps://", "mss://", "mtqp://", "mumble://", "mupdate://", "mvn://", "news://", "nfs://", "ni://", "nih://", "nntp://", "notes://", "ocf://", "oid://", "onenote://", "onenote-cmd://", "opaquelocktoken://", "openpgp4fpr://", "pack://", "palm://", "paparazzi://", "payto://", "pkcs11://", "platform://", "pop://", "pres://", "prospero://", "proxy://", "pwid://", "psyc://", "qb://", "query://", "redis://", "rediss://", "reload://", "res://", "resource://", "rmi://", "rsync://", "rtmfp://", "rtmp://", "rtsp://", "rtsps://", "rtspu://", "secondlife://", "service://", "session://", "sftp://", "sgn://", "shttp://", "sieve://", "simpleledger://", "sip://", "sips://", "skype://", "smb://", "sms://", "smtp://", "snews://", "snmp://", "soap.beep://", "soap.beeps://", "soldat://", "spiffe://", "spotify://", "ssh://", "steam://", "stun://", "stuns://", "submit://", "svn://", "tag://", "teamspeak://", "tel://", "teliaeid://", "telnet://", "tftp://", "things://", "thismessage://", "tip://", "tn3270://", "tool://", "turn://", "turns://", "tv://", "udp://", "unreal://", "urn://", "ut2004://", "v-event://", "vemmi://", "ventrilo://", "videotex://", "vnc://", "view-source://", "wais://", "webcal://", "wpid://", "ws://", "wss://", "wtai://", "wyciwyg://", "xcon://", "xcon-userid://", "xfire://", "xmlrpc.beep://", "xmlrpc.beeps://", "xmpp://", "xri://", "ymsgr://", "z39.50://", "z39.50r://", "z39.50s://", ""};

   private static String[] schemes = {"ftp://", "http://", "https://", ""};

   private static String[] prefixes = {"www.google", "a-website", "A-WEBSITE", "sub.domain", "lots.of.sub.domains.here", "cgj.kpq.vxyz", "a.domain.with.lots.of.sub.domains.to.test.long.subdomains.for.full.testing.so.lets.get.a.few.more.subdomains.in.there"};

   /* from https://www.icann.org/resources/pages/tlds-2012-02-25-en */
   private  static String[] tlds = {".AAA", ".AARP", ".ABARTH", ".ABB", ".ABBOTT", ".ABBVIE", ".ABC", ".ABLE", ".ABOGADO", ".ABUDHABI", ".AC", ".ACADEMY", ".ACCENTURE", ".ACCOUNTANT", ".ACCOUNTANTS", ".ACO", ".ACTOR", ".AD", ".ADAC", ".ADS", ".ADULT", ".AE", ".AEG", ".AERO", ".AETNA", ".AF", ".AFAMILYCOMPANY", ".AFL", ".AFRICA", ".AG", ".AGAKHAN", ".AGENCY", ".AI", ".AIG", ".AIGO", ".AIRBUS", ".AIRFORCE", ".AIRTEL", ".AKDN", ".AL", ".ALFAROMEO", ".ALIBABA", ".ALIPAY", ".ALLFINANZ", ".ALLSTATE", ".ALLY", ".ALSACE", ".ALSTOM", ".AM", ".AMERICANEXPRESS", ".AMERICANFAMILY", ".AMEX", ".AMFAM", ".AMICA", ".AMSTERDAM", ".ANALYTICS", ".ANDROID", ".ANQUAN", ".ANZ", ".AO", ".AOL", ".APARTMENTS", ".APP", ".APPLE", ".AQ", ".AQUARELLE", ".AR", ".ARAB", ".ARAMCO", ".ARCHI", ".ARMY", ".ARPA", ".ART", ".ARTE", ".AS", ".ASDA", ".ASIA", ".ASSOCIATES", ".AT", ".ATHLETA", ".ATTORNEY", ".AU", ".AUCTION", ".AUDI", ".AUDIBLE", ".AUDIO", ".AUSPOST", ".AUTHOR", ".AUTO", ".AUTOS", ".AVIANCA", ".AW", ".AWS", ".AX", ".AXA", ".AZ", ".AZURE", ".BA", ".BABY", ".BAIDU", ".BANAMEX", ".BANANAREPUBLIC", ".BAND", ".BANK", ".BAR", ".BARCELONA", ".BARCLAYCARD", ".BARCLAYS", ".BAREFOOT", ".BARGAINS", ".BASEBALL", ".BASKETBALL", ".BAUHAUS", ".BAYERN", ".BB", ".BBC", ".BBT", ".BBVA", ".BCG", ".BCN", ".BD", ".BE", ".BEATS", ".BEAUTY", ".BEER", ".BENTLEY", ".BERLIN", ".BEST", ".BESTBUY", ".BET", ".BF", ".BG", ".BH", ".BHARTI", ".BI", ".BIBLE", ".BID", ".BIKE", ".BING", ".BINGO", ".BIO", ".BIZ", ".BJ", ".BLACK", ".BLACKFRIDAY", ".BLOCKBUSTER", ".BLOG", ".BLOOMBERG", ".BLUE", ".BM", ".BMS", ".BMW", ".BN", ".BNL", ".BNPPARIBAS", ".BO", ".BOATS", ".BOEHRINGER", ".BOFA", ".BOM", ".BOND", ".BOO", ".BOOK", ".BOOKING", ".BOSCH", ".BOSTIK", ".BOSTON", ".BOT", ".BOUTIQUE", ".BOX", ".BR", ".BRADESCO", ".BRIDGESTONE", ".BROADWAY", ".BROKER", ".BROTHER", ".BRUSSELS", ".BS", ".BT", ".BUDAPEST", ".BUGATTI", ".BUILD", ".BUILDERS", ".BUSINESS", ".BUY", ".BUZZ", ".BV", ".BW", ".BY", ".BZ", ".BZH", ".CA", ".CAB", ".CAFE", ".CAL", ".CALL", ".CALVINKLEIN", ".CAM", ".CAMERA", ".CAMP", ".CANCERRESEARCH", ".CANON", ".CAPETOWN", ".CAPITAL", ".CAPITALONE", ".CAR", ".CARAVAN", ".CARDS", ".CARE", ".CAREER", ".CAREERS", ".CARS", ".CARTIER", ".CASA", ".CASE", ".CASEIH", ".CASH", ".CASINO", ".CAT", ".CATERING", ".CATHOLIC", ".CBA", ".CBN", ".CBRE", ".CBS", ".CC", ".CD", ".CEB", ".CENTER", ".CEO", ".CERN", ".CF", ".CFA", ".CFD", ".CG", ".CH", ".CHANEL", ".CHANNEL", ".CHARITY", ".CHASE", ".CHAT", ".CHEAP", ".CHINTAI", ".CHRISTMAS", ".CHROME", ".CHRYSLER", ".CHURCH", ".CI", ".CIPRIANI", ".CIRCLE", ".CISCO", ".CITADEL", ".CITI", ".CITIC", ".CITY", ".CITYEATS", ".CK", ".CL", ".CLAIMS", ".CLEANING", ".CLICK", ".CLINIC", ".CLINIQUE", ".CLOTHING", ".CLOUD", ".CLUB", ".CLUBMED", ".CM", ".CN", ".CO", ".COACH", ".CODES", ".COFFEE", ".COLLEGE", ".COLOGNE", ".COM", ".COMCAST", ".COMMBANK", ".COMMUNITY", ".COMPANY", ".COMPARE", ".COMPUTER", ".COMSEC", ".CONDOS", ".CONSTRUCTION", ".CONSULTING", ".CONTACT", ".CONTRACTORS", ".COOKING", ".COOKINGCHANNEL", ".COOL", ".COOP", ".CORSICA", ".COUNTRY", ".COUPON", ".COUPONS", ".COURSES", ".CR", ".CREDIT", ".CREDITCARD", ".CREDITUNION", ".CRICKET", ".CROWN", ".CRS", ".CRUISE", ".CRUISES", ".CSC", ".CU", ".CUISINELLA", ".CV", ".CW", ".CX", ".CY", ".CYMRU", ".CYOU", ".CZ", ".DABUR", ".DAD", ".DANCE", ".DATA", ".DATE", ".DATING", ".DATSUN", ".DAY", ".DCLK", ".DDS", ".DE", ".DEAL", ".DEALER", ".DEALS", ".DEGREE", ".DELIVERY", ".DELL", ".DELOITTE", ".DELTA", ".DEMOCRAT", ".DENTAL", ".DENTIST", ".DESI", ".DESIGN", ".DEV", ".DHL", ".DIAMONDS", ".DIET", ".DIGITAL", ".DIRECT", ".DIRECTORY", ".DISCOUNT", ".DISCOVER", ".DISH", ".DIY", ".DJ", ".DK", ".DM", ".DNP", ".DO", ".DOCS", ".DOCTOR", ".DODGE", ".DOG", ".DOHA", ".DOMAINS", ".DOT", ".DOWNLOAD", ".DRIVE", ".DTV", ".DUBAI", ".DUCK", ".DUNLOP", ".DUNS", ".DUPONT", ".DURBAN", ".DVAG", ".DVR", ".DZ", ".EARTH", ".EAT", ".EC", ".ECO", ".EDEKA", ".EDU", ".EDUCATION", ".EE", ".EG", ".EMAIL", ".EMERCK", ".ENERGY", ".ENGINEER", ".ENGINEERING", ".ENTERPRISES", ".EPSON", ".EQUIPMENT", ".ER", ".ERICSSON", ".ERNI", ".ES", ".ESQ", ".ESTATE", ".ESURANCE", ".ET", ".ETISALAT", ".EU", ".EUROVISION", ".EUS", ".EVENTS", ".EVERBANK", ".EXCHANGE", ".EXPERT", ".EXPOSED", ".EXPRESS", ".EXTRASPACE", ".FAGE", ".FAIL", ".FAIRWINDS", ".FAITH", ".FAMILY", ".FAN", ".FANS", ".FARM", ".FARMERS", ".FASHION", ".FAST", ".FEDEX", ".FEEDBACK", ".FERRARI", ".FERRERO", ".FI", ".FIAT", ".FIDELITY", ".FIDO", ".FILM", ".FINAL", ".FINANCE", ".FINANCIAL", ".FIRE", ".FIRESTONE", ".FIRMDALE", ".FISH", ".FISHING", ".FIT", ".FITNESS", ".FJ", ".FK", ".FLICKR", ".FLIGHTS", ".FLIR", ".FLORIST", ".FLOWERS", ".FLY", ".FM", ".FO", ".FOO", ".FOOD", ".FOODNETWORK", ".FOOTBALL", ".FORD", ".FOREX", ".FORSALE", ".FORUM", ".FOUNDATION", ".FOX", ".FR", ".FREE", ".FRESENIUS", ".FRL", ".FROGANS", ".FRONTDOOR", ".FRONTIER", ".FTR", ".FUJITSU", ".FUJIXEROX", ".FUN", ".FUND", ".FURNITURE", ".FUTBOL", ".FYI", ".GA", ".GAL", ".GALLERY", ".GALLO", ".GALLUP", ".GAME", ".GAMES", ".GAP", ".GARDEN", ".GB", ".GBIZ", ".GD", ".GDN", ".GE", ".GEA", ".GENT", ".GENTING", ".GEORGE", ".GF", ".GG", ".GGEE", ".GH", ".GI", ".GIFT", ".GIFTS", ".GIVES", ".GIVING", ".GL", ".GLADE", ".GLASS", ".GLE", ".GLOBAL", ".GLOBO", ".GM", ".GMAIL", ".GMBH", ".GMO", ".GMX", ".GN", ".GODADDY", ".GOLD", ".GOLDPOINT", ".GOLF", ".GOO", ".GOODYEAR", ".GOOG", ".GOOGLE", ".GOP", ".GOT", ".GOV", ".GP", ".GQ", ".GR", ".GRAINGER", ".GRAPHICS", ".GRATIS", ".GREEN", ".GRIPE", ".GROCERY", ".GROUP", ".GS", ".GT", ".GU", ".GUARDIAN", ".GUCCI", ".GUGE", ".GUIDE", ".GUITARS", ".GURU", ".GW", ".GY", ".HAIR", ".HAMBURG", ".HANGOUT", ".HAUS", ".HBO", ".HDFC", ".HDFCBANK", ".HEALTH", ".HEALTHCARE", ".HELP", ".HELSINKI", ".HERE", ".HERMES", ".HGTV", ".HIPHOP", ".HISAMITSU", ".HITACHI", ".HIV", ".HK", ".HKT", ".HM", ".HN", ".HOCKEY", ".HOLDINGS", ".HOLIDAY", ".HOMEDEPOT", ".HOMEGOODS", ".HOMES", ".HOMESENSE", ".HONDA", ".HONEYWELL", ".HORSE", ".HOSPITAL", ".HOST", ".HOSTING", ".HOT", ".HOTELES", ".HOTELS", ".HOTMAIL", ".HOUSE", ".HOW", ".HR", ".HSBC", ".HT", ".HU", ".HUGHES", ".HYATT", ".HYUNDAI", ".IBM", ".ICBC", ".ICE", ".ICU", ".ID", ".IE", ".IEEE", ".IFM", ".IKANO", ".IL", ".IM", ".IMAMAT", ".IMDB", ".IMMO", ".IMMOBILIEN", ".IN", ".INC", ".INDUSTRIES", ".INFINITI", ".INFO", ".ING", ".INK", ".INSTITUTE", ".INSURANCE", ".INSURE", ".INT", ".INTEL", ".INTERNATIONAL", ".INTUIT", ".INVESTMENTS", ".IO", ".IPIRANGA", ".IQ", ".IR", ".IRISH", ".IS", ".ISELECT", ".ISMAILI", ".IST", ".ISTANBUL", ".IT", ".ITAU", ".ITV", ".IVECO", ".JAGUAR", ".JAVA", ".JCB", ".JCP", ".JE", ".JEEP", ".JETZT", ".JEWELRY", ".JIO", ".JLL", ".JM", ".JMP", ".JNJ", ".JO", ".JOBS", ".JOBURG", ".JOT", ".JOY", ".JP", ".JPMORGAN", ".JPRS", ".JUEGOS", ".JUNIPER", ".KAUFEN", ".KDDI", ".KE", ".KERRYHOTELS", ".KERRYLOGISTICS", ".KERRYPROPERTIES", ".KFH", ".KG", ".KH", ".KI", ".KIA", ".KIM", ".KINDER", ".KINDLE", ".KITCHEN", ".KIWI", ".KM", ".KN", ".KOELN", ".KOMATSU", ".KOSHER", ".KP", ".KPMG", ".KPN", ".KR", ".KRD", ".KRED", ".KUOKGROUP", ".KW", ".KY", ".KYOTO", ".KZ", ".LA", ".LACAIXA", ".LADBROKES", ".LAMBORGHINI", ".LAMER", ".LANCASTER", ".LANCIA", ".LANCOME", ".LAND", ".LANDROVER", ".LANXESS", ".LASALLE", ".LAT", ".LATINO", ".LATROBE", ".LAW", ".LAWYER", ".LB", ".LC", ".LDS", ".LEASE", ".LECLERC", ".LEFRAK", ".LEGAL", ".LEGO", ".LEXUS", ".LGBT", ".LI", ".LIAISON", ".LIDL", ".LIFE", ".LIFEINSURANCE", ".LIFESTYLE", ".LIGHTING", ".LIKE", ".LILLY", ".LIMITED", ".LIMO", ".LINCOLN", ".LINDE", ".LINK", ".LIPSY", ".LIVE", ".LIVING", ".LIXIL", ".LK", ".LLC", ".LOAN", ".LOANS", ".LOCKER", ".LOCUS", ".LOFT", ".LOL", ".LONDON", ".LOTTE", ".LOTTO", ".LOVE", ".LPL", ".LPLFINANCIAL", ".LR", ".LS", ".LT", ".LTD", ".LTDA", ".LU", ".LUNDBECK", ".LUPIN", ".LUXE", ".LUXURY", ".LV", ".LY", ".MA", ".MACYS", ".MADRID", ".MAIF", ".MAISON", ".MAKEUP", ".MAN", ".MANAGEMENT", ".MANGO", ".MAP", ".MARKET", ".MARKETING", ".MARKETS", ".MARRIOTT", ".MARSHALLS", ".MASERATI", ".MATTEL", ".MBA", ".MC", ".MCKINSEY", ".MD", ".ME", ".MED", ".MEDIA", ".MEET", ".MELBOURNE", ".MEME", ".MEMORIAL", ".MEN", ".MENU", ".MERCKMSD", ".METLIFE", ".MG", ".MH", ".MIAMI", ".MICROSOFT", ".MIL", ".MINI", ".MINT", ".MIT", ".MITSUBISHI", ".MK", ".ML", ".MLB", ".MLS", ".MM", ".MMA", ".MN", ".MO", ".MOBI", ".MOBILE", ".MOBILY", ".MODA", ".MOE", ".MOI", ".MOM", ".MONASH", ".MONEY", ".MONSTER", ".MOPAR", ".MORMON", ".MORTGAGE", ".MOSCOW", ".MOTO", ".MOTORCYCLES", ".MOV", ".MOVIE", ".MOVISTAR", ".MP", ".MQ", ".MR", ".MS", ".MSD", ".MT", ".MTN", ".MTR", ".MU", ".MUSEUM", ".MUTUAL", ".MV", ".MW", ".MX", ".MY", ".MZ", ".NA", ".NAB", ".NADEX", ".NAGOYA", ".NAME", ".NATIONWIDE", ".NATURA", ".NAVY", ".NBA", ".NC", ".NE", ".NEC", ".NET", ".NETBANK", ".NETFLIX", ".NETWORK", ".NEUSTAR", ".NEW", ".NEWHOLLAND", ".NEWS", ".NEXT", ".NEXTDIRECT", ".NEXUS", ".NF", ".NFL", ".NG", ".NGO", ".NHK", ".NI", ".NICO", ".NIKE", ".NIKON", ".NINJA", ".NISSAN", ".NISSAY", ".NL", ".NO", ".NOKIA", ".NORTHWESTERNMUTUAL", ".NORTON", ".NOW", ".NOWRUZ", ".NOWTV", ".NP", ".NR", ".NRA", ".NRW", ".NTT", ".NU", ".NYC", ".NZ", ".OBI", ".OBSERVER", ".OFF", ".OFFICE", ".OKINAWA", ".OLAYAN", ".OLAYANGROUP", ".OLDNAVY", ".OLLO", ".OM", ".OMEGA", ".ONE", ".ONG", ".ONL", ".ONLINE", ".ONYOURSIDE", ".OOO", ".OPEN", ".ORACLE", ".ORANGE", ".ORG", ".ORGANIC", ".ORIGINS", ".OSAKA", ".OTSUKA", ".OTT", ".OVH", ".PA", ".PAGE", ".PANASONIC", ".PARIS", ".PARS", ".PARTNERS", ".PARTS", ".PARTY", ".PASSAGENS", ".PAY", ".PCCW", ".PE", ".PET", ".PF", ".PFIZER", ".PG", ".PH", ".PHARMACY", ".PHD", ".PHILIPS", ".PHONE", ".PHOTO", ".PHOTOGRAPHY", ".PHOTOS", ".PHYSIO", ".PIAGET", ".PICS", ".PICTET", ".PICTURES", ".PID", ".PIN", ".PING", ".PINK", ".PIONEER", ".PIZZA", ".PK", ".PL", ".PLACE", ".PLAY", ".PLAYSTATION", ".PLUMBING", ".PLUS", ".PM", ".PN", ".PNC", ".POHL", ".POKER", ".POLITIE", ".PORN", ".POST", ".PR", ".PRAMERICA", ".PRAXI", ".PRESS", ".PRIME", ".PRO", ".PROD", ".PRODUCTIONS", ".PROF", ".PROGRESSIVE", ".PROMO", ".PROPERTIES", ".PROPERTY", ".PROTECTION", ".PRU", ".PRUDENTIAL", ".PS", ".PT", ".PUB", ".PW", ".PWC", ".PY", ".QA", ".QPON", ".QUEBEC", ".QUEST", ".QVC", ".RACING", ".RADIO", ".RAID", ".RE", ".READ", ".REALESTATE", ".REALTOR", ".REALTY", ".RECIPES", ".RED", ".REDSTONE", ".REDUMBRELLA", ".REHAB", ".REISE", ".REISEN", ".REIT", ".RELIANCE", ".REN", ".RENT", ".RENTALS", ".REPAIR", ".REPORT", ".REPUBLICAN", ".REST", ".RESTAURANT", ".REVIEW", ".REVIEWS", ".REXROTH", ".RICH", ".RICHARDLI", ".RICOH", ".RIGHTATHOME", ".RIL", ".RIO", ".RIP", ".RMIT", ".RO", ".ROCHER", ".ROCKS", ".RODEO", ".ROGERS", ".ROOM", ".RS", ".RSVP", ".RU", ".RUGBY", ".RUHR", ".RUN", ".RW", ".RWE", ".RYUKYU", ".SA", ".SAARLAND", ".SAFE", ".SAFETY", ".SAKURA", ".SALE", ".SALON", ".SAMSCLUB", ".SAMSUNG", ".SANDVIK", ".SANDVIKCOROMANT", ".SANOFI", ".SAP", ".SARL", ".SAS", ".SAVE", ".SAXO", ".SB", ".SBI", ".SBS", ".SC", ".SCA", ".SCB", ".SCHAEFFLER", ".SCHMIDT", ".SCHOLARSHIPS", ".SCHOOL", ".SCHULE", ".SCHWARZ", ".SCIENCE", ".SCJOHNSON", ".SCOR", ".SCOT", ".SD", ".SE", ".SEARCH", ".SEAT", ".SECURE", ".SECURITY", ".SEEK", ".SELECT", ".SENER", ".SERVICES", ".SES", ".SEVEN", ".SEW", ".SEX", ".SEXY", ".SFR", ".SG", ".SH", ".SHANGRILA", ".SHARP", ".SHAW", ".SHELL", ".SHIA", ".SHIKSHA", ".SHOES", ".SHOP", ".SHOPPING", ".SHOUJI", ".SHOW", ".SHOWTIME", ".SHRIRAM", ".SI", ".SILK", ".SINA", ".SINGLES", ".SITE", ".SJ", ".SK", ".SKI", ".SKIN", ".SKY", ".SKYPE", ".SL", ".SLING", ".SM", ".SMART", ".SMILE", ".SN", ".SNCF", ".SO", ".SOCCER", ".SOCIAL", ".SOFTBANK", ".SOFTWARE", ".SOHU", ".SOLAR", ".SOLUTIONS", ".SONG", ".SONY", ".SOY", ".SPACE", ".SPORT", ".SPOT", ".SPREADBETTING", ".SR", ".SRL", ".SRT", ".SS", ".ST", ".STADA", ".STAPLES", ".STAR", ".STARHUB", ".STATEBANK", ".STATEFARM", ".STC", ".STCGROUP", ".STOCKHOLM", ".STORAGE", ".STORE", ".STREAM", ".STUDIO", ".STUDY", ".STYLE", ".SU", ".SUCKS", ".SUPPLIES", ".SUPPLY", ".SUPPORT", ".SURF", ".SURGERY", ".SUZUKI", ".SV", ".SWATCH", ".SWIFTCOVER", ".SWISS", ".SX", ".SY", ".SYDNEY", ".SYMANTEC", ".SYSTEMS", ".SZ", ".TAB", ".TAIPEI", ".TALK", ".TAOBAO", ".TARGET", ".TATAMOTORS", ".TATAR", ".TATTOO", ".TAX", ".TAXI", ".TC", ".TCI", ".TD", ".TDK", ".TEAM", ".TECH", ".TECHNOLOGY", ".TEL", ".TELEFONICA", ".TEMASEK", ".TENNIS", ".TEVA", ".TF", ".TG", ".TH", ".THD", ".THEATER", ".THEATRE", ".TIAA", ".TICKETS", ".TIENDA", ".TIFFANY", ".TIPS", ".TIRES", ".TIROL", ".TJ", ".TJMAXX", ".TJX", ".TK", ".TKMAXX", ".TL", ".TM", ".TMALL", ".TN", ".TO", ".TODAY", ".TOKYO", ".TOOLS", ".TOP", ".TORAY", ".TOSHIBA", ".TOTAL", ".TOURS", ".TOWN", ".TOYOTA", ".TOYS", ".TR", ".TRADE", ".TRADING", ".TRAINING", ".TRAVEL", ".TRAVELCHANNEL", ".TRAVELERS", ".TRAVELERSINSURANCE", ".TRUST", ".TRV", ".TT", ".TUBE", ".TUI", ".TUNES", ".TUSHU", ".TV", ".TVS", ".TW", ".TZ", ".UA", ".UBANK", ".UBS", ".UCONNECT", ".UG", ".UK", ".UNICOM", ".UNIVERSITY", ".UNO", ".UOL", ".UPS", ".US", ".UY", ".UZ", ".VA", ".VACATIONS", ".VANA", ".VANGUARD", ".VC", ".VE", ".VEGAS", ".VENTURES", ".VERISIGN", ".VERSICHERUNG", ".VET", ".VG", ".VI", ".VIAJES", ".VIDEO", ".VIG", ".VIKING", ".VILLAS", ".VIN", ".VIP", ".VIRGIN", ".VISA", ".VISION", ".VISTAPRINT", ".VIVA", ".VIVO", ".VLAANDEREN", ".VN", ".VODKA", ".VOLKSWAGEN", ".VOLVO", ".VOTE", ".VOTING", ".VOTO", ".VOYAGE", ".VU", ".VUELOS", ".WALES", ".WALMART", ".WALTER", ".WANG", ".WANGGOU", ".WARMAN", ".WATCH", ".WATCHES", ".WEATHER", ".WEATHERCHANNEL", ".WEBCAM", ".WEBER", ".WEBSITE", ".WED", ".WEDDING", ".WEIBO", ".WEIR", ".WF", ".WHOSWHO", ".WIEN", ".WIKI", ".WILLIAMHILL", ".WIN", ".WINDOWS", ".WINE", ".WINNERS", ".WME", ".WOLTERSKLUWER", ".WOODSIDE", ".WORK", ".WORKS", ".WORLD", ".WOW", ".WS", ".WTC", ".WTF", ".XBOX", ".XEROX", ".XFINITY", ".XIHUAN", ".XIN", ".XN--11B4C3D", ".XN--1CK2E1B", ".XN--1QQW23A", ".XN--2SCRJ9C", ".XN--30RR7Y", ".XN--3BST00M", ".XN--3DS443G", ".XN--3E0B707E", ".XN--3HCRJ9C", ".XN--3OQ18VL8PN36A", ".XN--3PXU8K", ".XN--42C2D9A", ".XN--45BR5CYL", ".XN--45BRJ9C", ".XN--45Q11C", ".XN--4GBRIM", ".XN--54B7FTA0CC", ".XN--55QW42G", ".XN--55QX5D", ".XN--5SU34J936BGSG", ".XN--5TZM5G", ".XN--6FRZ82G", ".XN--6QQ986B3XL", ".XN--80ADXHKS", ".XN--80AO21A", ".XN--80AQECDR1A", ".XN--80ASEHDB", ".XN--80ASWG", ".XN--8Y0A063A", ".XN--90A3AC", ".XN--90AE", ".XN--90AIS", ".XN--9DBQ2A", ".XN--9ET52U", ".XN--9KRT00A", ".XN--B4W605FERD", ".XN--BCK1B9A5DRE4C", ".XN--C1AVG", ".XN--C2BR7G", ".XN--CCK2B3B", ".XN--CG4BKI", ".XN--CLCHC0EA0B2G2A9GCD", ".XN--CZR694B", ".XN--CZRS0T", ".XN--CZRU2D", ".XN--D1ACJ3B", ".XN--D1ALF", ".XN--E1A4C", ".XN--ECKVDTC9D", ".XN--EFVY88H", ".XN--ESTV75G", ".XN--FCT429K", ".XN--FHBEI", ".XN--FIQ228C5HS", ".XN--FIQ64B", ".XN--FIQS8S", ".XN--FIQZ9S", ".XN--FJQ720A", ".XN--FLW351E", ".XN--FPCRJ9C3D", ".XN--FZC2C9E2C", ".XN--FZYS8D69UVGM", ".XN--G2XX48C", ".XN--GCKR3F0F", ".XN--GECRJ9C", ".XN--GK3AT1E", ".XN--H2BREG3EVE", ".XN--H2BRJ9C", ".XN--H2BRJ9C8C", ".XN--HXT814E", ".XN--I1B6B1A6A2E", ".XN--IMR513N", ".XN--IO0A7I", ".XN--J1AEF", ".XN--J1AMH", ".XN--J6W193G", ".XN--JLQ61U9W7B", ".XN--JVR189M", ".XN--KCRX77D1X4A", ".XN--KPRW13D", ".XN--KPRY57D", ".XN--KPU716F", ".XN--KPUT3I", ".XN--L1ACC", ".XN--LGBBAT1AD8J", ".XN--MGB9AWBF", ".XN--MGBA3A3EJT", ".XN--MGBA3A4F16A", ".XN--MGBA7C0BBN0A", ".XN--MGBAAKC7DVF", ".XN--MGBAAM7A8H", ".XN--MGBAB2BD", ".XN--MGBAH1A3HJKRD", ".XN--MGBAI9AZGQP6J", ".XN--MGBAYH7GPA", ".XN--MGBB9FBPOB", ".XN--MGBBH1A", ".XN--MGBBH1A71E", ".XN--MGBC0A9AZCG", ".XN--MGBCA7DZDO", ".XN--MGBERP4A5D4AR", ".XN--MGBGU82A", ".XN--MGBI4ECEXP", ".XN--MGBPL2FH", ".XN--MGBT3DHD", ".XN--MGBTX2B", ".XN--MGBX4CD0AB", ".XN--MIX891F", ".XN--MK1BU44C", ".XN--MXTQ1M", ".XN--NGBC5AZD", ".XN--NGBE9E0A", ".XN--NGBRX", ".XN--NODE", ".XN--NQV7F", ".XN--NQV7FS00EMA", ".XN--NYQY26A", ".XN--O3CW4H", ".XN--OGBPF8FL", ".XN--OTU796D", ".XN--P1ACF", ".XN--P1AI", ".XN--PBT977C", ".XN--PGBS0DH", ".XN--PSSY2U", ".XN--Q9JYB4C", ".XN--QCKA1PMC", ".XN--QXAM", ".XN--RHQV96G", ".XN--ROVU88B", ".XN--RVC1E0AM3E", ".XN--S9BRJ9C", ".XN--SES554G", ".XN--T60B56A", ".XN--TCKWE", ".XN--TIQ49XQYJ", ".XN--UNUP4Y", ".XN--VERMGENSBERATER-CTB", ".XN--VERMGENSBERATUNG-PWB", ".XN--VHQUV", ".XN--VUQ861B", ".XN--W4R85EL8FHU5DNRA", ".XN--W4RS40L", ".XN--WGBH1C", ".XN--WGBL6A", ".XN--XHQ521B", ".XN--XKC2AL3HYE2A", ".XN--XKC2DL3A5EE0H", ".XN--Y9A3AQ", ".XN--YFRO4I67O", ".XN--YGBI2AMMX", ".XN--ZFR164B", ".XXX", ".XYZ", ".YACHTS", ".YAHOO", ".YAMAXUN", ".YANDEX", ".YE", ".YODOBASHI", ".YOGA", ".YOKOHAMA", ".YOU", ".YOUTUBE", ".YT", ".YUN", ".ZA", ".ZAPPOS", ".ZARA", ".ZERO", ".ZIP", ".ZM", ".ZONE", ".ZUERICH", ".ZW"};

   private static String[] ports = {"", ":0", ":1", ":80", ":65535"};

   private static String[] paths = {"/", "/path/", "/a/long/path"};

   private static String[] queries = {"", "?key=value", "?key=value&anotherkey=anothervalue"};

   private static String[][] elements = {schemes, prefixes, tlds, ports, paths, queries};

   /**
    * Default schemes.
    */
   private static String[] defaultSchemes = { "http", "https", "ftp" };

   /**
    * Http only scheme.
    */
   private static String[] httpScheme = { "http" };

   /**
    * A regex pattern matcher for a valid scheme.
    */
   private static final Pattern VALID_SCHEME = Pattern.compile("^([a-z][a-z0-9+\\-.]*)");

   /**
    * The number of random tests to run.
    */
   private static final int RANDOM_TEST_COUNT = 1000;

   /**
    * A random url part generator.
    */
   private static final RandomUrlPartGenerator randomUrlPartGenerator = new RandomUrlPartGenerator();

   /**
    * A default UrlValidator. Valid schemes are http, https, and ftp.
    */
   private UrlValidator defaultUrlValidator = new UrlValidator();
   /**
    * A UrlValidator with only "http" as the valid scheme.
    */
   private UrlValidator httpUrlValidator = new UrlValidator(httpScheme);
   /**
    * A UrlValidator that allows all schemes.
    */
   private UrlValidator allowAllSchemesValidator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   /**
    * Tests random valid schemes.
    */
   public void testValidSchemes() {
      final String urlEnd = "://www.google.com";
      // http should be valid for all

      for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
         final String url = randomUrlPartGenerator.getValidScheme() + urlEnd;
         if (url.startsWith("http://")) {
            assertTrue(httpUrlValidator.isValid(url));
            assertTrue(defaultUrlValidator.isValid(url));
         } else if (url.startsWith("https://")) {
            assertFalse(httpUrlValidator.isValid(url));
            assertTrue(defaultUrlValidator.isValid(url));
         } else if (url.startsWith("ftp://")) {
            assertFalse(httpUrlValidator.isValid(url));
            assertTrue(defaultUrlValidator.isValid(url));
         } else {
            assertFalse(httpUrlValidator.isValid(url));
            assertFalse(defaultUrlValidator.isValid(url));
         }
         assertTrue(allowAllSchemesValidator.isValid(url));
      }
   }

   /**
    * Tests random invalid schemes.
    */
   public void testInvalidSchemes() {
      final String urlEnd = "://www.google.com";
      for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
         final String url = randomUrlPartGenerator.getInvalidScheme() + urlEnd;
         assertFalse(httpUrlValidator.isValid(url));
         assertFalse(defaultUrlValidator.isValid(url));
         assertFalse(allowAllSchemesValidator.isValid(url));
      }
   }

   /**
    * Tests random valid authorities.
    */
   public void testValidAuthorities() {
      final String urlStart = "http://";
      StringBuilder sb = new StringBuilder();
      for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
         final String url = urlStart + randomUrlPartGenerator.getValidAuthority();
         assertTrue(httpUrlValidator.isValid(url));
         assertTrue(defaultUrlValidator.isValid(url));
         assertTrue(allowAllSchemesValidator.isValid(url));
      }
   }

   /**
    * Tests random invalid authorities.
    */
   public void testInvalidAuthorities() {
      final String urlStart = "http://";
      StringBuilder sb = new StringBuilder();
      for (int i = 0; i < RANDOM_TEST_COUNT; i++) {
         final String url = urlStart + randomUrlPartGenerator.getInvalidAuthority();
         assertFalse(httpUrlValidator.isValid(url));
         assertFalse(defaultUrlValidator.isValid(url));
         assertFalse(allowAllSchemesValidator.isValid(url));
      }
   }

   public void testManualTest()
   {
//You can use this function to implement your manual testing
      assertTrue(httpUrlValidator.isValid("http://www.google.com/"));
   }

   private String getNextCombination(int[] bounds, int[] counters) {
      StringBuilder string = new StringBuilder();
      for (int i = 0; i < bounds.length; i++) {
         if (bounds[i] == counters[i] + 1) {
            counters[i] = 0;
            string.append(elements[i][counters[i]].toLowerCase());
         } else {
            counters[i]++;
            while (i < bounds.length) {
               string.append(elements[i][counters[i]].toLowerCase());
               i++;
            }
            return string.toString();
         }
      }
      return null;
   }

   private FileWriter getLogger() {
      /* this can all be commented out or put to terminal output if desired,
       *  but there are a lot of failures so the default is file output */
      File file = new File("testIsValid.out");
      if (file.exists()) { file.delete(); }
      FileWriter logger = null;
      try {
         logger = new FileWriter("testIsValid.out", false);
         logger.append("Invalid Urls Found (with exceptions as appropriate):\n");
      } catch (IOException e) {
         System.out.println("File open error. Not all invalid Urls will be written to file.");
         e.printStackTrace();
      }
      return logger;
   }

   private void closeLogger(FileWriter logger) {
      try {
         logger.close();
      } catch (IOException e) {
         System.out.println("File close error.");
         e.printStackTrace();
      }
   }

   private long countCases(int[] bounds) {
      long cases = 1;
      for (int i = 0; i < bounds.length; i++) {
         cases = cases * bounds[i];
      }
      return cases;
   }

   private void writeInvalidCases(StringBuilder invalids, FileWriter logger) {
      try {
         logger.append(invalids.toString());
      } catch (IOException e) {
         System.out.println("File writer error. Not all invalid Urls will be written to file.");
         e.printStackTrace();
      }
   }
   
   public void testIsValid() {
      UrlValidator validator = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES +
              UrlValidator.NO_FRAGMENTS);
      long tests = 0;
      long passes = 0;
      long exceptions = 0;
      StringBuilder invalids = new StringBuilder();
      FileWriter logger = getLogger();

      int[] bounds = {schemes.length, prefixes.length, tlds.length, ports.length,
              paths.length, queries.length};
      int[] counters = new int[bounds.length];
      counters[0] = -1; // getNextCombination will increment this the first run

      System.out.println("Running programmed tests over " + countCases(bounds) + " test cases...");
      String string = getNextCombination(bounds, counters);
      while (string != null) {
         tests++;
         boolean result = false;
         /* This prevents any kind of Throwable problem from being caught, notably
         *  anytime you use a scheme with the validator other than "" it can't seem to
         *  address it and halts execution in line 393 without the try/catch below. */
         try {
            result = validator.isValid(string);
         } catch (Throwable e) {
            exceptions++;
            invalids.append(e.toString() + " on Url: ");
         }
         if (result) {
            //System.out.println("Valid: " + string); // use for printing valid results if desired
            passes++;
         } else {
            invalids.append(string + "\n");
         }
         string = getNextCombination(bounds ,counters);
         if (invalids.length() >= 10000) {
            writeInvalidCases(invalids, logger);
            invalids = new StringBuilder();
         }
      }

      writeInvalidCases(invalids, logger);
      closeLogger(logger);
      float ratio = (float)passes / tests;
      System.out.printf("Results-exceptions:%d passes:%d ratio(pass/total):%f",
              exceptions, passes, ratio);
      assertEquals(passes, tests); // this nearly always fails, the validator is quite buggy!
   }
}
