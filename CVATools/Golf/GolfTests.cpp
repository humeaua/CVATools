//
//  GolfTests.cpp
//  CVATools
//
//  Created by Alexandre HUMEAU on 11/01/15.
//
//

#include "RegressionTests.h"

#include "Player.h"
#include "Tournament.h"
#include "GreaterScoreSorter.h"
#include "DummyRandomSimulator.h"
#include "Rankings.h"
#include "PointsSystemStaticData.h"
#include "RankingPointSystem.h"
#include "TourFwdDecl.h"
#include "ValueSimulator.h"
#include "TieHandler.h"
#include "OWGRVectorWrapper.h"
#include "PlayerDispatcher.h"

#include <cmath>
#include <sstream>
#include <iomanip>
#include <numeric>

#include "RegressionTestMacros.h"

bool RegressionTest::PlayerResultTest() const
{
    PlayerResult result1("Tournament1", Utilities::Date::MyDate(30,9,2014), 30, 288, 1.5);
    
    
    REGRESSIONTESTRETURNONFAILURE(!result1.MissedCut())
    REGRESSIONTESTRETURNONFAILURE(result1.Position() == 30)
    REGRESSIONTESTRETURNONFAILURE(result1.Score() == 288)
    REGRESSIONTESTRETURNONFAILURE(result1.RankingPoints() == 1.5)
    
    REGRESSIONTESTRETURNSUCCESS
}

bool RegressionTest::DummyTournament() const
{
    Tournament tournament("dummy",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,PGATOUR));
    const size_t numPlayers = 100;
    std::vector<Player> players(numPlayers,Player("",PGATOUR)); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str(),PGATOUR);
        
        tournament.AddPlayer(players[i]);
    }
    
    Rankings rankings(PointsSystemStaticData::GetOWGRInterpolator());
    RankingPointSystem rankingPtSystem(rankings);
    tournament.SetPointsTo1st(rankingPtSystem);
    
    tournament.Simulate(DummyRandomSimulator(0));
    
    tournament.Rank(GreaterScoreSorter());
    
    size_t refValues[] = {2146335337,2139642574,2132723841,2116969294,2097549478,2091824407,2085187937,2064010129,2055540383,2042297871,2002830094,1950367213,1906706780,1846443803,1840335376,1830665860,1809249219,1797288065,1793547003,1791277536,1789614810,1779175845,1741849297,1734177661,1731106012,1719408956,1710028745,1671889999,1669187896,1664792818,1643550337,1579802159,1567674295,1566369460,1559526673,1514888112,1500357984,1462087311,1461728458,1370738826,1359072203,1294600846,1290446329,1269870926,1163120341,1152891831,1094100450,1073226880,1046126087,1040043610,1028169396,1009021007,1006609540,1002898451,968021766,926881476,899316322,897787792,892086236,890459872,838023412,822784415,819516268,810662187,809673979,792526220,764058775,763654014,679469414,675891343,664835076,631361083,608455363,590294128,569022154,525706991,520932930,515529753,496586426,480849991,428300259,422527594,400151788,393860762,309696691,250591794,247074805,210367714,205711490,158379552,145532761,115120654,77268269,68362598,66433441,57271926,52107318,28925691,27706653,19932546};
    Tournament::Players & tournamentPlayers = tournament.GetPlayers();
    
    size_t error = 0;
    for (size_t player = 0 ; player < tournamentPlayers.size() ; ++player)
    {
        error += std::abs((long)tournamentPlayers[player].second.Score() - (long)refValues[player]);
    }
    
    REGRESSIONTESTRETURNONFAILURE(error<1)
    
    size_t error2 = 0;
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].AddResult(tournament);
    }
    
    const size_t rank[] = {76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32};
    
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        error2 += std::abs((long)rank[player] - (long)players[player].Results()[0].Position());
    }
    
    REGRESSIONTESTRETURNONFAILURE(error2 < 1)
    
    Utilities::Date::MyDate tomorrow(19,12,2014);
    rankings.Compute(std::vector<Tournament>(1, tournament), tomorrow);
    
#ifdef _DEBUG
    m_logger.PutLine(rankings.ToString());
#endif
    
    REGRESSIONTESTRETURNSUCCESS
}

bool RegressionTest::StaticDataRanking() const
{
    //  Test of static data used in the ranking
    
    m_logger.PutLine("Interpolator : ");
    Utilities::Interp::Interpolator & linear = PointsSystemStaticData::GetOWGRInterpolator();
    
    const double refValuesInterpolator[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0.971428571428571,0.914285714285714,0.857142857142857,0.8,0.742857142857142,0.685714285714285,0.628571428571428,0.571428571428571,0.514285714285714,0.457142857142857,0.399999999999999,0.342857142857142,0.285714285714285,0.228571428571428,0.171428571428571,0.114285714285714,0.0571428571428563,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double errorInterpolator = 0;
    int i = 0;
    for (double x = -2 ; x < 4.0 ; x += 0.1, i++)
    {
        errorInterpolator += std::abs(refValuesInterpolator[i] - linear(x));
    }
    const double tolerance = 1e-10;
    REGRESSIONTESTRETURNONFAILURE(errorInterpolator<tolerance)
    
    m_logger.PutLine("Home Rating Value : ");
    std::vector<double> & homeRatingValue = PointsSystemStaticData::GetHomeRatingValues();
    const double refValuesHomeRating[] = {8,7,6,5,4,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    double errorHomeRating = 0.0;
    for (size_t i = 0 ; i < homeRatingValue.size() ; ++i)
    {
        errorHomeRating += std::abs(refValuesHomeRating[i]-homeRatingValue[i]);
    }
    
    REGRESSIONTESTRETURNONFAILURE(errorHomeRating < tolerance && homeRatingValue.size() == 30)
    
    m_logger.PutLine("World Event Rating Value : ");
    std::vector<double> & worldEventRatingValue = PointsSystemStaticData::GetEventRatingValues();
    const double refValueEventRating[] = {45,37,32,27,24,21,20,19,18,17,16,15,14,13,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,10,10,10,10,9,9,9,9,8,8,8,8,8,7,7,7,7,7,7,7,6,6,6,6,6,5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    double errorEventRating = 0.0;
    for (size_t i = 0 ; i < worldEventRatingValue.size() ; ++i)
    {
        errorEventRating += std::abs(refValueEventRating[i]-worldEventRatingValue[i]);
    }
    REGRESSIONTESTRETURNONFAILURE(errorHomeRating < tolerance && worldEventRatingValue.size() == 200)
    
    m_logger.PutLine("Total Rating to 1st point : ");
    Utilities::Interp::Interpolator & totalRatingTo1stPoint = PointsSystemStaticData::GetTotalRatingToFirstPointInterpolator();
    const double refValuestotalRatingTo1stPoints [] = {6,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,11,11,11,11,11,12,12,12,12,12,13,13,13,13,13,14,14,14,14,14,15,15,15,15,15,16,16,16,16,16,17,17,17,17,17,18,18,18,18,18,19,19,19,19,19,20,20,20,20,20,21,21,21,21,21,22,22,22,22,22,22,22,22,22,22,23,23,23,23,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80};
    double errorTotalRatingTo1stPoint = 0.0;
    i = 0;
    for (double d = 0 ; d < 1000 ; ++d, ++i)
    {
        errorTotalRatingTo1stPoint += std::abs(refValuestotalRatingTo1stPoints[i] - totalRatingTo1stPoint(d));
    }
    
    REGRESSIONTESTRETURNONFAILURE(errorTotalRatingTo1stPoint < tolerance && totalRatingTo1stPoint.size() == 93)
    
    m_logger.PutLine("Points compared to 1st : ");
    const OWGRVectorWrapper<double> & pointsComparedTo1st = PointsSystemStaticData::PointsComparedTo1st();
    const double refValuesPointsComparedTo1st[] = {100,60,40,30,24,20,18,16,15,14,13,12,11,10,9.5,9,8.5,8,7.5,7,6.5,6,5.8,5.6,5.4,5.2,5,4.8,4.6,4.5,4.4,4.3,4.2,4.1,4,3.9,3.8,3.7,3.6,3.5,3.4,3.3,3.2,3.1,3,2.9,2.8,2.7,2.6,2.5,2.4,2.3,2.2,2.1,2,1.9,1.8,1.7,1.6,1.5,1.5,1.5,1.5,1.5,1.5};
    double errorPointsComparedTo1st = 0.0;
    for (size_t i = 0 ; i < pointsComparedTo1st.size() ; ++i)
    {
        errorPointsComparedTo1st += std::abs(pointsComparedTo1st[i] - refValuesPointsComparedTo1st[i]);
    }
    
    REGRESSIONTESTRETURN(errorPointsComparedTo1st < tolerance)
}

bool RegressionTest::MultipleTournamentsSameWeek() const
{
    Tournament pgatourTournament("dummyPGA",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,PGATOUR)), europeantourTournament("dummyEuro",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,EUROPEANTOUR));
    const size_t numPlayers = 200;
    std::vector<Player> players(numPlayers,Player("",PGATOUR)); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers / 2 ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str(),PGATOUR);
        
        pgatourTournament.AddPlayer(players[i]);
    }
    for (size_t i = numPlayers / 2 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str(),EUROPEANTOUR);
        
        europeantourTournament.AddPlayer(players[i]);
    }
    
    Rankings rankings(PointsSystemStaticData::GetOWGRInterpolator());
    RankingPointSystem rankingPtSystem(rankings);
    pgatourTournament.SetPointsTo1st(rankingPtSystem);
    europeantourTournament.SetPointsTo1st(rankingPtSystem);
    
    pgatourTournament.Simulate(DummyRandomSimulator(0));
    europeantourTournament.Simulate(DummyRandomSimulator(0));
    
    pgatourTournament.Rank(GreaterScoreSorter());
    europeantourTournament.Rank(GreaterScoreSorter());
    
    size_t refValues[] = {2146335337,2139642574,2132723841,2116969294,2097549478,2091824407,2085187937,2064010129,2055540383,2042297871,2002830094,1950367213,1906706780,1846443803,1840335376,1830665860,1809249219,1797288065,1793547003,1791277536,1789614810,1779175845,1741849297,1734177661,1731106012,1719408956,1710028745,1671889999,1669187896,1664792818,1643550337,1579802159,1567674295,1566369460,1559526673,1514888112,1500357984,1462087311,1461728458,1370738826,1359072203,1294600846,1290446329,1269870926,1163120341,1152891831,1094100450,1073226880,1046126087,1040043610,1028169396,1009021007,1006609540,1002898451,968021766,926881476,899316322,897787792,892086236,890459872,838023412,822784415,819516268,810662187,809673979,792526220,764058775,763654014,679469414,675891343,664835076,631361083,608455363,590294128,569022154,525706991,520932930,515529753,496586426,480849991,428300259,422527594,400151788,393860762,309696691,250591794,247074805,210367714,205711490,158379552,145532761,115120654,77268269,68362598,66433441,57271926,52107318,28925691,27706653,19932546};
    Tournament::Players & tournamentPlayersPGA = pgatourTournament.GetPlayers();
    Tournament::Players & tournamentPlayersEuro = europeantourTournament.GetPlayers();
    
    size_t error = 0;
    for (size_t player = 0 ; player < tournamentPlayersPGA.size() ; ++player)
    {
        error += std::abs((long)tournamentPlayersPGA[player].second.Score() - (long)refValues[player]);
    }
    for (size_t player = 0 ; player < tournamentPlayersEuro.size() ; ++player)
    {
        error += std::abs((long)tournamentPlayersEuro[player].second.Score() - (long)refValues[player]);
    }
    
    REGRESSIONTESTRETURNONFAILURE(error < 1)
    
    size_t error2 = 0;
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].AddResult(pgatourTournament);
        players[player].AddResult(europeantourTournament);
    }
    
    const size_t rank[] = {76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32,76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32};
    
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        error2 += std::abs((long)rank[player] - (long)players[player].Results()[0].Position());
    }
    
    REGRESSIONTESTRETURNONFAILURE(error2 < 1)
    
    Utilities::Date::MyDate tomorrow(19,12,2014);
    std::vector<Tournament> thisWeekTournaments;
    thisWeekTournaments.push_back(pgatourTournament);
    thisWeekTournaments.push_back(europeantourTournament);
    
    rankings.Compute(thisWeekTournaments, tomorrow);
    
#ifdef _DEBUG
    m_logger.PutLine(rankings.ToString());
#endif
    
    REGRESSIONTESTRETURNSUCCESS
}

bool RegressionTest::CoSanctionedTournament() const
{
    std::vector<TourType> tourTypes(2);
    tourTypes[0] = PGATOUR;
    tourTypes[1] = CHALLENGETOUR;
    
    Tournament tournament("dummyEuro",Utilities::Date::MyDate(14,01,2015), tourTypes);
    m_logger.PutLine("CoSanctioned ? ");
    const bool isCoSanctioned = tournament.CoSanctionedEvent();
    
    REGRESSIONTESTRETURNONFAILURE(isCoSanctioned)
    
    m_logger.PutLine("Ranking points : ");
    Rankings rankings(PointsSystemStaticData::GetOWGRInterpolator());
    RankingPointSystem rankingPtSystem(rankings);
    tournament.SetPointsTo1st(rankingPtSystem);
    const double rankingPoints = tournament.GetPointsTo1st();
    const double refValue = 18.0, tolerance = 1e-15;
    
    REGRESSIONTESTRETURN(std::abs(rankingPoints-refValue) < tolerance)
}

bool RegressionTest::TieHandler() const
{
    //  Design a test when the tie handler is fully designed
    Tournament tournament("dummy",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,PGATOUR));
    const size_t numPlayers = 100;
    std::vector<Player> players(numPlayers,Player("",PGATOUR)); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str(), PGATOUR);
        
        tournament.AddPlayer(players[i]);
    }
    
    Rankings rankings(PointsSystemStaticData::GetOWGRInterpolator());
    RankingPointSystem rankingPtSystem(rankings);
    tournament.SetPointsTo1st(rankingPtSystem);
    
    tournament.Simulate(ValueSimulator(0));
    Tournament::Players & players0 = tournament.GetPlayers();
    std::sort(players0.begin(), players0.end(), [](const std::pair<PlayerID, PlayerResult> & lhs, const std::pair<PlayerID, PlayerResult> & rhs)
              {
                  return lhs.second.Score() > rhs.second.Score();
              }
);
    
    //  Enable Tie handler when the class is fully working
    OWGRVectorWrapper<double> pointsComparedTo1st = PointsSystemStaticData::PointsComparedTo1st();
    double refValue = 0;
    for (size_t i = 0 ; i < players.size() ; ++i)
    {
        refValue += pointsComparedTo1st[i];
    }
    class TieHandler tieHandler;
    tieHandler.Update(players0, pointsComparedTo1st);
    OWGRVectorWrapper<double> adjustedPoints = tieHandler.GetAdjustedPoints();
    double sum = 0;
    for (size_t i = 0 ; i < adjustedPoints.size() ; ++i)
    {
        sum += adjustedPoints[i];
    }
    
    const double tolerance = 1e-10;
    REGRESSIONTESTRETURN(std::abs(sum - refValue) < tolerance)
}

bool RegressionTest::Tours() const
{
    std::vector<Tour_ptr> tours;
    tours.push_back(std::tr1::shared_ptr<Tour>(new PGATour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new EuropeanTour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new ChallengeTour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new WebComTour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new AsianTour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new JapanTour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new SunshineTour));
    tours.push_back(std::tr1::shared_ptr<Tour>(new PGATourCanada));
    
    Tournament dummy("dummy", Utilities::Date::MyDate(25,01,2015), std::vector<TourType>());
    double refValues[] = {24,24,12,14,14,14,14,6};
    const double tolerance = 1e-14;
    double error = 0;
    size_t i = 0;
    for (std::vector<Tour_ptr>::iterator tour = tours.begin() ; tour != tours.end() ; ++tour, ++i)
    {
        error += std::abs(refValues[i] - (*tour)->MinimumRankingPoints(dummy));
        
    }
    
    REGRESSIONTESTRETURN(error < tolerance)
}

bool RegressionTest::OWGRVectorWrapperTest() const
{
    OWGRVectorWrapper<double> wrapper(2,0.0);
    wrapper.push_back(1.0);
    
    const double refValues[] = {0,0,1,1,1};
    double error = 0;
    const double tolerance = 1e-10;
    for (size_t i = 0 ; i < 5 ; ++i)
    {
        error += std::abs(refValues[i]-wrapper[i]);
    }
    
    REGRESSIONTESTRETURN(error < tolerance)
}

bool RegressionTest::Major() const
{
    Tournament augusta("MASTERS", Utilities::Date::MyDate(14,4,2015), std::vector<TourType>(1,MAJOR));
    Rankings rankings(PointsSystemStaticData::GetOWGRInterpolator());
    RankingPointSystem rankingPtSystem(rankings);
    augusta.SetPointsTo1st(rankingPtSystem);
    const double rankingPoints = augusta.GetPointsTo1st();
    
    const double refValue = 100.0, tolerance = 1e-14;
    
    REGRESSIONTESTRETURN(std::abs(refValue - rankingPoints) < tolerance)
}

bool RegressionTest::PlayerDispatcher() const
{
    Tournament pgatourTournament("dummyPGA",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,PGATOUR)), europeantourTournament("dummyEuro",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,EUROPEANTOUR));
    
    const size_t numPlayers = 200;
    std::vector<Player> players(numPlayers,Player("",PGATOUR)); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers / 2 ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str(),PGATOUR);
    }
    for (size_t i = numPlayers / 2 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str(),EUROPEANTOUR);
    }
    
    long long seed = 0;
    const double in_proba = 0.4, out_proba = 0.1;
    class PlayerDispatcher dispatcher(in_proba, out_proba, seed);
    
    std::vector<Tournament> tournaments;
    tournaments.push_back(pgatourTournament);
    tournaments.push_back(europeantourTournament);
    
    const std::string refValue[] = {"Player 0",
        "Player 1",
        "Player 6",
        "Player 21",
        "Player 25",
        "Player 35",
        "Player 40",
        "Player 41",
        "Player 55",
        "Player 57",
        "Player 60",
        "Player 76",
        "Player 83",
        "Player 87",
        "Player 100",
        "Player 101",
        "Player 104",
        "Player 112",
        "Player 138",
        "Player 150",
        "Player 164",
        "Player 165",
        "Player 179",
        "Player 199",
        "Player 27",
        "Player 37",
        "Player 52",
        "Player 65",
        "Player 90",
        "Player 103",
        "Player 133",
        "Player 135",
        "Player 167",
        "Player 189"};
    
    dispatcher.Dispatch(players, tournaments);
    
    double error = 0.0;
    size_t index = 0;
    for (size_t i = 0 ; i < 2 ; ++i)
    {
        const Tournament::Players players = tournaments[i].GetPlayers();
        for (size_t j = 0 ; j < players.size() ; ++j)
        {
            if (players[j].first.Name().c_str() != refValue[index])
            {
                error += 1.0;
            }
            index++;
        }
    }
    
    REGRESSIONTESTRETURN(error == 0)
}