//
//  RandomNumberTests.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 22/02/15.
//
//

#include "RegressionTests.h"

#include "BernouilliGenerator.h"
#include <sstream>
#include "NormalGenerator.h"
#include <iomanip>
#include "DiscreteGenerator.h"

bool RegressionTest::Bernouilli() const
{
    long long seed = 0L;
    BernouilliGenerator bernouilli(seed, 0.5);
    
    size_t NRealisations = 1000;
    const double refValues[] = {1,1,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,1,0,0,1,0,1,1,0,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,0,0,0,1,1,1,0,0,0,1,0,1,1,1,1,1,1,1,0,1,0,0,1,1,0,1,1,1,0,0,1,0,0,0,0,0,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,0,0,1,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,1,0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,0,1,1,1,0,0,1,0,1,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,0,0,0,1,0,0,1,0,0,0,0,0,1,1,0,1,1,0,1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,1,1,1,0,1,1,0,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,0,1,0,1,1,0,1,0,0,0,0,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,0,1,1,1,1,0,1,0,1,0,0,1,0,1,0,0,0,1,1,1,0,1,0,0,0,0,0,1,1,0,1,1,1,1,0,1,0,1,0,1,0,1,0,0,0,1,0,1,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,1,0,0,0,0,1,1,1,1,0,1,1,1,1,1,0,0,1,0,0,1,0,1,1,0,1,0,1,1,1,1,0,0,1,1,0,1,1,0,1,1,0,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,0,0,0,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1,0,0,0,1,0,0,0,1,1,0,1,0,0,0,1,0,1,1,0,0,0,0,1,0,1,1,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1,0,1,0,0,1,1,1,0,1,0,1,0,1,1,0,1,1,0,1,0,1,1,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,0,0,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,0,0,1,0,1,1,0,0,1,1,1,0,1,0,0,1,1,1,1,1,1,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0,1,0,1,1,0,1,0,1,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,1,1,0,1,0,1,0,1,0,0,1,1,0,0,1,0,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,0,0,0,1,0,1,1,1,0,0,0,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,0,1,1,1,1,0,0,1,0,0,1,0,0,1,0,1,0,0,1,0,0,1,1,0,0,1,1,0,0,0,1,0,1,0,0,0,0,0,1,1,1,0,1,0,1,1,1,1,1,1,0,0,1,0,0,0,1,0,0,1,0,1,1,0,0,0,1,1,0,1,0,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1,0,1,0,0,1,0,1,0,1,1,0,1,1,0,0,1,0,1,1,1,1,0,0,0,1,0,1,0,0,0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,0,1,0,0,0,0,0,1,0,1,1,1,1,0,0,1,1,1,0,1,1,0,1,1,1,1,0,1,0,1,0,0,0,1,1,1,0,0,1,0,0,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,0,1};
    
    double error = 0, sum = 0, stdev = 0;
    std::stringstream errorReporting;
    for (size_t i = 0 ; i < NRealisations ; ++i)
    {
        const double ber = bernouilli();
        errorReporting << ber << "," ;
        error += std::abs(refValues[i]-ber);
        sum += refValues[i];
        stdev += refValues[i] * refValues[i];
    }
    
    sum /= NRealisations;
    stdev /= NRealisations;
    stdev -= sum * sum;
    
    const double tolerance = 1e-10;
    
    if (error < tolerance)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        m_logger.PutLine(errorReporting.str());
        return false;
    }
}

bool RegressionTest::Normal() const
{
    long long seed = 0L;
    NormalGenerator<double> normal(seed, 0, 1);
    
    const size_t NRealisations = 1000;
    double refValues[] = {-0.0251500499779632,0.350523616332935,1.05280061045995,-0.880476180681887,0.610705273835537,-0.412999804127539,0.632048885424655,0.563921113636843,0.157925158278126,-1.47433645113963,-2.00255212238799,0.759725182366755,1.15518882834383,0.420274904309286,1.32639592997379,0.318394940650546,0.268291520064554,2.44909816478823,0.184601614246948,-1.4983854096968,-0.833222674595694,-0.86229663809218,-0.227242418953428,0.873198234105938,-0.297821441373544,-0.00492846413236436,-0.592442130814152,0.265759249864983,-0.466761753437028,0.38859722340274,0.111207575629034,1.2283671072024,-0.194421283478685,-0.764178981309183,1.01115743048914,0.4840409725598,1.6122481625777,0.963284305171239,1.74254016053824,1.12577700803026,-0.0874022392366084,-0.231287714629614,0.498957952366545,-1.39902024120603,-0.105841359300948,-0.354227217950335,0.272337345418967,-1.82174138426405,0.53160550744185,-0.0674483464367212,0.665472988044311,1.2346906556216,-1.02437919028638,-0.0205755430057468,-0.761360370939709,0.541384232344442,-0.982019755549195,0.287236422234516,-0.468855108800879,0.513631459842818,0.831721969429832,1.31233545086441,-1.10931732610245,-0.483517588345536,0.831388701093618,1.50490220733664,1.79983815624299,1.70128151914631,0.685486214810873,0.931463189476563,0.774313904550401,-0.0758476732181567,0.497940438065544,-1.32855527415081,-0.0733476362043653,-0.455870045454014,-0.128811346293832,-0.290165149583823,-0.920647187454906,0.162316082284517,-0.25166548239268,-1.4223201409471,1.05926807906701,-0.9369931783564,1.0047173999496,-0.224579481158642,1.08252302361569,0.649970683993801,-1.57313818355013,0.92166258461247,-1.1353344942634,0.686621670517092,1.03158818475002,-0.0304899372533135,-0.0729362988966235,-1.52979809496837,0.450505018366311,1.21454039112717,-0.318487044969067,-1.40710673987687,-0.0110659169645997,1.06431137580588,-0.300636992026511,-1.73949074640493,-0.522334122079572,-0.999121845836937,0.537303947041122,0.448692671302876,1.7360527114146,0.806327401260888,1.24577511327998,-0.486310792992482,0.206848895419596,0.899491038716449,0.742267627431697,-0.16237606879306,1.05198984395885,2.02846651662044,0.294423777420699,1.32977600476543,0.485501705623708,-0.178622165616633,1.15820930111296,0.813493226559698,-1.66996652771714,0.214598320726922,-0.888669630519068,-0.254404323931982,-0.099166738800991,0.827334627907594,-0.831507386104932,-0.530073697743046,0.240641622910381,0.568387567399367,-1.29946113974589,0.172857849873067,-0.313906824648741,0.200409218664023,-0.812368211635773,-1.02130668714477,0.944329509872033,1.73158999390854,0.257907087847733,-1.25102098105841,-0.0743837415703253,1.64415728352352,-1.22905079246157,-0.603432141101017,0.561022108506958,1.071770034659,-1.45904807211871,0.273662703490132,2.02930281114176,-0.154670744586106,-0.421021842732551,-0.182118445125406,-0.445018202077635,0.678497449129913,0.358160338426147,0.878002207014759,0.513664279702265,0.569157986539414,0.930858283774756,1.30336342473559,-0.210090561068604,-0.197788219498861,2.16225758711797,-0.32440928422875,0.132499301558102,0.0996044133967087,0.78773107391678,-0.545658159999846,0.442268908238844,-1.16315927413414,1.2654842212334,1.10632080715033,2.23366511739914,2.13994510133697,0.539878155400773,0.655434514478861,1.6515504626828,-0.708772200574121,0.904869921478449,0.589034950638776,1.36187046568897,0.386919640404378,1.35610369457133,1.8777241998522,-0.970444294850827,-0.434583446464862,0.934753154629157,0.577249794627418,-2.00789538200399,0.39703136364607,0.337276048934815,0.874201574260205,-0.472563955226694,0.671745758149229,-0.962100386712158,1.05677431811657,1.05442279251161,-1.12120854154708,0.869339735495073,0.133778459938826,0.0116021229072884,-0.725974461365885,0.111245969056433,-1.65271196460986,-1.49553076174486,1.40137249546607,-0.162041984424096,0.454223359438692,0.740654831879911,1.25759911356843,-0.427907767518468,0.051868060237689,-0.951679380222193,-0.825266879928234,-0.484593721306152,-0.10524697630457,0.825371561754276,-0.189370553698956,-0.330830657853861,-0.148729068769955,0.98056097432268,-0.808712085597413,-1.30491839422004,-0.872186124771238,-1.37934703324387,-1.03225772962301,-0.878895048044839,1.0475767445186,-2.68795263554363,1.64984276494844,0.397620509579356,0.0162363736690951,-0.771255063735453,0.681049859608498,1.71550482004954,1.10905152977059,-0.270942854747217,-1.57698567832274,-0.0701676305070005,-1.38169504724427,0.322342299393485,-0.437183138389331,0.407199953632234,0.226606646740408,-0.567931021168698,-0.856552967933255,0.951744687716656,1.08582316217732,-0.407531875376562,-0.451435903307797,0.170341916295729,-2.1202145916263,1.89247510113199,0.424707986978631,-1.98803018735169,0.269445045993428,-0.306735434330453,0.787494243605336,1.31722032480895,-1.36052208766008,-1.24286049357952,-1.033549239947,2.06340111573762,-0.394034930943548,-0.971138569866159,-0.22981870715116,-0.662460043363177,-0.316462860785591,1.17263691496617,0.705067633632352,1.20387041778436,0.667699529984233,0.395529073421412,2.48461629787315,0.460928530031274,1.90072367257742,0.900894785567925,1.17913528078544,-0.175418518419209,-0.694542345202006,1.89903439299027,-1.03012002085265,-0.457123825553936,0.609356625520439,1.20133385078991,0.781911496495392,0.933037003227319,0.912822463697719,0.134880429537275,-0.288715756604651,-1.1593451017093,1.25277855341835,-0.708161052579562,-1.73548987060543,-0.193466846937272,1.10073874192346,0.628886278442798,1.90955736562421,-0.741132650035364,0.383684772723266,0.368764138300867,-0.0961831697136959,-0.321839018410316,0.855156245852677,-0.136590149310631,-0.946074486715078,-1.1274105406416,0.873642228915383,0.147759546840488,-0.295481538322789,0.784507032707042,-0.2266603896125,0.607128459420196,0.153955479398269,0.286649634853941,-0.200090605857451,0.395171867630948,1.02976407107791,0.0138064205292624,1.07472414769121,0.726911658810236,0.025124527275509,1.57107139935503,-0.164060524933749,0.178014188349833,0.924497488330131,0.579617451446876,1.67536893185194,-0.17206155504312,0.304186799023773,-0.970927839925969,0.674935094366403,-0.178529077000013,-1.99408066599252,-0.86355485226183,-0.699003943853009,0.700031290119685,-0.46931367139716,0.839278803563903,1.18015352697669,0.499698346611599,0.9039228502323,0.334100214670061,0.64697144748235,-0.523918820751953,-0.0932144912198682,-0.136679958942723,-0.461761242595614,-0.667207569431874,-0.869035135868774,-1.22551440474322,-1.30645025047115,-2.38485848454825,-0.73605453084169,-0.442207761559373,0.768501772950708,-1.39152361998297,-0.613138506375472,-0.148774011767672,-2.198197959497,0.658325730483519,-1.43571741339772,1.30731851224769,0.556600590678836,1.17345625330134,-0.714406766887814,0.860528433163561,3.38911958155945,-0.373374987088719,0.827514699055763,0.700353883278187,0.51574532393535,-0.835677244034712,-0.869704115727658,-3.53327353063276,-0.944868095855078,-0.832235369287902,0.675199425978236,0.443553440332667,0.261360090466384,1.51992705199936,-0.290759530335201,-0.6409653013629,-2.49403799872508,-0.241368532529189,-0.369859046966987,-1.15098586419848,0.781021385299031,-0.802388282835716,0.63436978927807,0.786570078006287,-0.514612621542517,0.601967202306335,0.574469254824095,0.402544541561854,1.6601359695377,0.40509827948677,-1.82231385924515,0.0615089626314582,-0.737570226236182,-0.310508786017295,-1.74891074181693,-0.393833265328331,0.242973977639663,-0.18926727420405,1.66648961825606,-0.836599545883341,0.613951089915586,-0.570728398105785,0.573371235101148,-1.26142882946681,-0.379888668471957,-0.243831643006678,0.635945921943976,-1.8750833254015,-0.476869291111636,-1.92086110664272,-1.91423003652191,-1.43294017979391,0.683129359285601,-1.63153674254301,0.0574678656691925,-0.0811495281992567,-0.499714762600445,-1.00855587234405,-0.474889678313202,0.675162089524822,0.866923862945656,1.47503740993953,2.47605593898469,0.711615491640286,-0.84415880544547,-0.457262618670088,-0.759051046774289,-2.64810069002982,-0.127553072328723,-0.166161235382971,0.775175809567687,-1.89600345992412,-1.0697790619742,0.468408172345132,-0.349112064734148,-1.8167609993781,-0.305281286965815,-0.501831573947905,-0.142670563151618,1.17126012208801,-0.489584161486618,-0.205696852689608,0.00532170541678931,0.0121163917745684,1.3122917280394,-1.17417387992173,-0.664169209405269,0.308568248076091,0.228318449810125,-0.399010562936449,-0.712173537724114,-0.920240898392468,-0.307973850214656,-2.12528554313828,-0.451877696656818,-1.00443953606487,0.38678642628521,0.903021465209962,-1.80631778608988,-0.650697795480219,-1.15266826356434,-0.958839406677093,-1.38719530954949,-0.089349284262657,0.0453821559832836,-0.81708557304222,1.00515785675783,-0.735132177652133,1.45843098217318,-0.580159801654598,1.41788887935896,0.232402715034752,-0.709136643925867,1.38495018230435,0.0499421067489528,-0.113264792582564,0.0408002832136413,-0.278901853373144,0.376884057331998,-0.218622502853954,-0.425859715599665,-0.112132734239573,-1.77612092318505,-0.161968615760527,-1.07395808602492,-0.19737527988161,1.53149930365159,1.73384808792991,2.02897515665167,0.649995900899446,-2.30150124393436,0.659068979520713,-0.115431006501236,-0.685687237353282,1.28702987157609,-0.860942199279281,-1.15584255388742,-1.2312112505304,-0.51553370802089,-1.90321307516389,-0.0408133367175292,-0.0468564013535879,-0.534801268026361,1.18400952217619,0.716421564380387,-0.478777378147747,-0.854123143175374,-0.103541384618787,0.348923262627851,0.996040810503009,-0.489040603413262,0.278455288094394,-2.02582308079905,2.34467482512005,-1.29196308645454,-0.896834209529338,0.134121048937093,1.27400847699916,2.15698232330639,1.15355682578124,0.902661422478226,0.183180014302214,0.00203812443524236,0.856246883087448,3.54257770985257,-0.26214272006622,-1.50059253114376,0.45150279079805,-0.0861949909666125,-0.239272978558267,1.79662579608977,-0.115504567756911,0.60843195124818,-1.44863537946407,-0.26163258429357,-1.16629983822056,-0.362112920844523,-0.302743632214222,1.34810244411023,1.7479655966258,-0.372618285602354,-0.133270508725975,-0.532562330625911,0.762721611145358,-0.357838854918426,0.957159559687012,-0.155484065734814,-0.829566304643509,-2.59964867998468,-0.840202404568705,0.890378225276835,-1.37808346426005,1.47241564185139,-0.78033712036337,-2.03522723817642,-0.205044995727798,1.15996708764902,0.115117937412892,0.0491038537149838,-0.251672173244158,-1.84613722357216,0.166785604790109,-0.0147083049510364,1.09703844759379,0.317975010233701,0.211411480428001,-1.63898043962598,-0.205508403870465,-0.214893370200539,-0.46722568171192,-0.781113512384628,0.764387214705669,-1.13496190187298,-0.809446429779654,0.484602423934272,-0.885172724265772,1.59000562420521,-1.23338513973959,-0.281473638015605,0.0160473554563661,-0.271940596382209,-0.545326453434166,-0.383679700553256,-0.196521232535958,0.516134077403328,1.59950336016993,-2.31545801229403,0.253856122448191,0.693203709836794,0.99000130479189,-0.730290323831716,0.977813538483326,0.881530747658036,-1.00339217704558,-0.521922429213491,-0.221231840638841,1.23994702932988,-0.23543187648891,-1.05029957307965,-0.717277071569179,1.51505287105725,1.19377816130389,-1.21063067158809,0.358483771455054,1.73701225585316,0.977147954778595,0.159244607706348,-1.89191471287661,0.345491147560748,0.0955523184568769,2.10337286766291,-0.180504410723055,-0.170044560228114,0.528213580075421,1.29139749823949,-0.842151931535026,0.162171938020881,-1.37405425321386,-2.7675027676487,-0.206673720226139,0.485203849439396,0.599689497732138,0.00240553255155654,-0.992954878092962,-1.13104042708665,-0.577618353253052,1.53693606067053,1.39600476674031,-0.00830900490133954,1.4054496669783,-1.16470097942687,-1.33565870462665,-0.0785467589879575,-0.806346673376753,-1.64010557141072,-1.11326585538704,-0.400756698539787,0.939273775492137,-0.136980025548756,0.156006430717902,0.862010278320069,0.585817976905164,0.654333876276015,1.5949555916489,-0.610998675530864,-0.640812772781981,-1.52987964794071,-1.42508929811083,-0.590978428403139,-0.835727397078123,-1.43167048509722,1.33191559001631,-0.0133750637391058,0.358248238432853,-2.86277603729028,-0.512769536001888,0.0581249167502912,0.340394803708122,-0.614421395347406,-1.33202330877145,-0.0463719536079416,-1.82665846930774,0.338115161235924,0.699350774138177,-0.733850801537033,-0.865813629955141,0.801522913154295,0.0176616199899298,1.1083666634071,0.462019822932676,-1.70025961717556,0.637622853319195,1.71762484449007,-0.751733865732847,-1.00006401239315,0.512741810912341,-0.187934048337339,1.20646429154541,-0.255587549744871,-1.26686235763734,0.888416723846051,0.746331198950341,-0.450581231224275,-1.64139163432255,1.23548189638027,-0.188515124431831,0.548410991747556,0.0463303030304573,-0.192493104942802,1.08189812599702,0.85616823796807,-0.56754407423213,-0.229114367985688,-2.08685196004387,-0.0546205564768591,1.5837163455794,-0.758470734042759,-0.987571728322036,-1.14477450049147,-1.92097444463879,0.542378861331957,2.7771070494628,0.260090339919347,-0.850405770186322,-1.20835268979724,1.39280734164337,0.253541900117827,0.150784284127122,-0.0724461176270404,-0.685905246883331,0.724477503422626,-1.76049377626871,0.883844568576191,-1.42728034707014,-0.292948690522202,0.632489142159864,1.22392212226772,2.43381801889507,-1.71836778745916,0.134361553402743,-0.616889355991221,-1.55257172060592,0.513477218333843,1.31884154021344,0.325520162725062,0.615729029351414,-1.93334999383924,-1.24403595353154,-0.90123760183076,0.354548163442167,0.57683128758231,-0.444214325317621,0.20845615873863,-0.613810716869823,0.434742482065568,0.782519774960674,1.34067133189232,0.485363898429443,-1.02200025594589,0.0435990881869712,0.0604124718759164,-0.464831848035016,-2.09767058737412,1.51088540655026,0.953988585897238,0.952204061193107,0.0668871378701349,-0.0834357361008899,1.50169479410677,0.698284226444998,0.845595707378713,-1.89778856755279,0.532065368141688,0.955370107614049,0.0110505893372727,0.4821432577495,1.30058387550129,0.291742550408255,-0.856904737804362,-0.151121778523666,-0.174889239973506,0.00889740240715711,-0.227848591569849,-0.173023307699793,-0.392253725930437,-1.70913838528062,-0.271268825764257,0.823771064615047,-1.22761421504353,0.364854910239087,0.669543505353154,-0.448203072578443,-0.81864859903334,0.466004670544093,-1.24140183544545,-1.43941959987994,0.128151625722025,0.380159944991127,-0.182835121716112,0.909721640520588,-0.364840338838221,0.854104883105005,-1.74252661730819,1.23603041627965,0.972878156086441,0.117856358631874,-0.655379766406749,0.823700970303438,0.888112405820297,-1.13990780837457,-0.52978543420647,-0.703425977446087,-0.520819164014728,-0.111236308632593,0.266350770284719,2.52778272427374,1.65552420101795,-0.2730840793555,-0.83923147492195,1.41243416172954,0.276621933519045,-0.26742944796143,-0.920036486162797,1.26084606783967,-1.89690093064047,-0.261404514233849,-1.78332438690723,0.854889854148902,-1.67546563382886,-1.59935198220358,-1.30335226535542,0.594043253136904,-0.209385698751214,0.114528362286672,1.64203749793954,-1.33584280764891,0.913488431169791,-0.476887418282723,-1.2512720530826,-1.47351054560631,-0.786312005098649,-0.124398852881771,0.240604165577563,0.943734855868475,0.343499878602486,-0.847527421482366,-0.50119003693855,-1.47091743427507,1.23231405899557,0.634110307751686,0.250502519861377,-0.643646045518684,1.17965510696694,-1.75215993356746,-1.40085002078434,0.450401829597601,-0.237947679508556,-0.573235455999508,-0.389531943397747,-2.4573844956271,-0.865824880511953,1.13217515458264,0.0704126018223637,0.180287664107295,1.14947882181363,-1.38062830167598,-0.814619789779145,-1.0366755402743,-0.759547838910286,0.608727573640463,0.989140568296557,-1.15578827928917,-2.1001836811865,-1.38455305343855,-0.655773291965996,-0.764500093375422,-0.363014325823433,-0.488693987463879,-2.06434703210326,1.11665519938234,-1.3077903449802,0.00271222078023658,-0.757014808421379,-0.388772500096501,0.186695277985572,0.430967199852174,-0.160684804503067,-0.481000472381773,-0.639774563108309,-0.355593002299854,-0.525797904516477,0.0836029080477305,2.34663748265702,0.435572313258462,-1.13406688333005,2.2899030436685,1.63629836574026,-0.509526982989421,-0.629197475514657,-1.85052214786827,-0.322589523886267,0.771976233154328,-0.126450798543374,0.465459840059735,0.108265961926275,0.18525482495009,-0.230228457889085,-0.52857832908964,-0.137329032145044,0.300479347882068,0.225619929194738,-0.656345210129873,-0.250849532175921,0.968668454609313,0.3177838796428,-0.781934465775132,-1.46773793695662,-1.55568483198261,-0.096840832139618,-0.771396529980993,0.170737632482093,-2.38682171323291,-0.658281051959776,1.50039019588577,0.716432659168125,1.37354731505489,-0.337848410098639,0.443968791092556,-1.5166862948725,-2.16504566770153,-0.0475996555744669,0.890319617096796,-0.453659863805603,-1.55472440076173,0.244735765877764,-1.22031789881234,-0.300256913324079,0.518135364357946,0.0305954475120117,-0.277999148394539,0.15509388588451,0.448781798949029,0.869675811526472,2.29999191993114,0.645013745183065,0.742366261757604,-0.54356294680678,1.93021657454442,-1.77714563804514,-0.171464759356884,0.206918904174257,0.844097472462543,0.136472630636513,-1.25469237260519,1.39378994274864,1.71332566048649,-0.0143334607619231,-0.875055155901903,-0.0601314537918319,-1.9623487516735,-0.176473045370767,0.785241260930948,0.971549439288149,2.63265272648535,0.804973201406439,-1.05464594486373,1.69215038343539,0.660193263153108,-0.667784991168113,0.154646761358697,-0.901324609964707,-0.0489280341728116,-0.209137941656588,-0.134103975830802,-0.397874597295058,0.63799514904984,-1.3873854470936,-0.541571633214342,-0.753284382953817,0.797218037200107,-1.13429556378257,-1.07254973573784,0.917811307601301,0.582356897293661,-0.411483574013104,-1.44349129761814,1.26539549460943,0.055261373421879,-0.203978803270952,-1.0246583755953,1.43567786128287,-0.291632202949717,-0.746073464363021,-0.134293719966648,0.705493131538474,-0.332424293087134,-0.492083830882193,0.629526450068113,1.65282724510185,-0.205052719720586,-2.48780463326622,-1.98494820524969,0.737253599461607,-0.645511260294457,-0.0314489195115494,-1.10244997953112,0.181947492943774,-0.725757651073183,-0.747048297025981};
    double error = 0, sum = 0, stdev = 0;
    for (size_t i = 0 ; i < NRealisations ; ++i)
    {
        const double norm = normal();
        error += std::abs(refValues[i]-norm);
        sum += norm;
        stdev += norm * norm;
    }
    
    sum /= NRealisations;
    stdev /= NRealisations;
    stdev -= sum * sum;
    
    const double tolerance = 1e-12;
    
    if (error < tolerance)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        return false;
    }
}

bool RegressionTest::DiscreteDistribution() const
{
    std::vector<double> x, proba;
    x.push_back(1.0);
    proba.push_back(0.1);
    
    x.push_back(2.0);
    proba.push_back(0.2);
    
    x.push_back(3.0);
    proba.push_back(0.3);
    
    x.push_back(4.0);
    proba.push_back(0.4);
    
    unsigned int seed = 0;
    DiscreteGenerator<double> discreteDistribution(x, proba, seed);
    
    const size_t NRealisations = 1000;
    
    double error = 0, sum = 0, stdev = 0;
    std::stringstream errorReporting;
    errorReporting << std::setprecision(15);
    
    const double refValues[] = {2,1,3,3,1,4,3,4,1,1,4,4,3,3,4,2,4,2,4,3,4,4,2,2,3,3,1,4,1,4,4,3,1,4,2,4,2,4,4,4,2,3,3,4,3,1,4,3,4,1,2,3,1,3,4,3,4,4,3,3,4,1,4,3,4,2,4,4,4,4,4,4,4,1,3,4,3,3,3,4,2,4,3,2,2,3,2,3,4,3,4,2,4,4,4,3,4,2,1,4,2,2,4,2,3,1,3,3,2,4,4,4,2,4,1,2,3,4,4,3,4,4,3,4,3,4,2,2,3,4,2,3,4,1,3,1,4,2,4,1,4,2,3,3,3,3,3,1,4,4,3,4,4,1,2,1,3,2,4,3,4,3,2,2,3,3,4,1,3,3,4,1,4,2,4,2,4,4,2,4,3,4,3,4,2,4,3,2,4,3,4,4,3,3,4,4,3,3,4,2,1,4,4,3,4,3,3,1,4,2,4,4,3,2,2,4,2,1,4,4,4,4,3,3,2,4,3,4,3,1,4,4,3,3,4,3,4,4,3,4,2,3,4,4,4,2,2,1,4,4,4,2,1,4,3,2,2,2,2,4,4,4,3,2,3,4,3,3,1,4,3,4,3,4,3,3,1,4,4,4,2,4,2,4,1,4,4,4,3,3,4,4,3,3,3,1,1,3,3,3,2,1,3,4,2,4,2,3,2,3,4,3,1,3,3,4,1,3,4,4,1,4,4,4,3,4,4,4,3,4,4,2,4,4,4,2,2,4,3,3,1,3,4,2,4,3,2,2,4,4,4,4,4,4,3,4,3,2,2,3,4,3,4,3,4,3,3,3,3,3,4,4,2,4,4,2,3,4,4,4,2,4,2,2,3,4,4,4,4,2,2,4,4,2,2,4,4,4,4,4,3,1,3,3,4,4,1,4,4,4,4,4,3,2,4,4,3,2,3,4,1,4,1,1,4,2,3,4,2,4,3,4,4,3,4,3,4,4,2,3,3,4,1,4,2,4,4,3,3,3,3,1,3,4,3,3,4,1,1,3,3,3,3,4,3,4,1,1,4,3,1,3,2,2,4,1,2,3,4,1,4,3,3,3,2,3,3,4,4,2,2,3,3,4,2,4,3,3,1,3,4,4,4,3,4,1,4,4,4,4,3,4,4,3,3,2,3,4,2,4,3,3,2,4,4,2,3,4,1,2,3,4,2,4,4,4,2,2,3,3,4,1,4,2,3,3,4,2,4,3,4,4,3,2,4,3,2,1,3,3,4,4,4,4,3,2,4,4,4,2,4,3,3,3,3,3,4,4,3,4,2,4,3,4,3,4,4,4,4,1,3,2,4,4,4,3,4,3,1,3,2,2,3,4,3,4,4,3,4,2,4,2,3,3,4,3,4,4,4,4,1,3,4,4,2,3,3,4,4,3,4,3,2,4,1,4,3,4,4,3,3,2,3,3,4,3,3,2,4,3,2,3,4,4,1,3,4,2,3,2,3,4,2,4,2,4,4,4,3,1,2,1,4,2,3,3,3,4,3,4,3,3,3,2,3,1,4,3,2,3,4,1,1,2,3,1,2,4,3,4,4,2,1,4,3,4,3,4,1,3,4,3,1,3,4,3,3,3,4,3,4,3,1,4,4,4,2,4,4,4,4,4,4,4,2,4,4,3,1,3,2,4,4,3,3,4,3,4,3,4,3,2,4,4,3,4,3,1,3,3,3,1,4,3,3,4,3,1,3,1,4,4,3,4,1,4,3,3,2,3,3,3,3,1,3,3,2,1,4,3,4,3,4,3,2,1,1,4,4,3,2,4,4,4,2,3,4,1,4,4,2,2,3,4,2,2,3,4,3,4,3,4,2,3,4,4,2,4,3,4,1,3,2,3,1,3,3,2,1,1,2,4,4,3,4,4,4,4,3,4,1,4,4,3,2,3,3,2,3,2,3,3,4,4,4,4,1,3,2,4,4,3,3,1,2,3,4,3,3,2,1,4,3,4,3,4,4,3,2,3,2,1,4,3,4,4,4,3,3,4,1,2,1,4,4,1,4,2,4,4,2,4,3,3,3,4,2,4,3,4,2,3,3,1,2,3,1,4,4,2,2,4,3,2,4,2,4,4,1,2,3,4,2,4,1,3,4,2,2,3,4,3,3,3,2,3,3,2,1,4,4,4,3,2,4,4,1,4,3,4,4,4,4,2,1,4,4,1,2,1,2,2,3,3,2,4,4,2,4,3,1,4,3,3,3,3,3,3,4,4};
    for (size_t i = 0 ; i < NRealisations ; ++i)
    {
        const double norm = discreteDistribution();
        errorReporting << norm << "," ;
        error += std::abs(refValues[i]-norm);
        sum += norm;
        stdev += norm * norm;
    }
    
    sum /= NRealisations;
    stdev /= NRealisations;
    stdev -= sum * sum;
    
    const double tolerance = 1e-12;
    
    if (error < tolerance)
    {
        m_logger.PutLine("SUCCEEDED");
        return true;
    }
    else
    {
        m_logger.PutLine("FAILED");
        return false;
    }
    
    
    return false;
}