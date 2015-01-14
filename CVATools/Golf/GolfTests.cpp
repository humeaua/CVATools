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

#include <cmath>
#include <sstream>

bool RegressionTest::PlayerResultTest() const
{
    PlayerResult result1("Tournament1", Utilities::Date::MyDate(30,9,2014), 30, 288, 1.5);
    
    if (result1.MissedCut())
    {
        m_out << "Missed Cut is true" << std::endl;
        return false;
    }
    
    if (result1.Position() != 30)
    {
        m_out << "Position is not 30" << std::endl;
        return false;
    }
    
    if (result1.Score() != 288)
    {
        m_out << "Score is not 288" << std::endl;
        return false;
    }
    
    if (result1.RankingPoints() != 1.5)
    {
        m_out << "Ranking points is not 1.5" << std::endl;
        return false;
    }
    m_out << "SUCCEEDED" << std::endl;
    return true;
}

bool RegressionTest::DummyTournament() const
{
    Tournament tournament("dummy",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,PGATOUR));
    const size_t numPlayers = 100;
    std::vector<Player> players(numPlayers,std::string("")); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str());
        
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
        error += fabs(tournamentPlayers[player].second.Score() - refValues[player]);
#ifdef _DEBUG
        m_out << players[player].first.Name() << ":" << players[player].second.Score() << std::endl;
#endif
    }
    
    if (error < 1)
    {
        m_out << "Score : SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    size_t error2 = 0;
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].AddResult(tournament);
    }
    
    const size_t rank[] = {76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32};
    
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
#ifdef _DEBUG
        m_out << players[player].Results()[0].Position() << ",";
#endif
        error2 += fabs(rank[player] - players[player].Results()[0].Position());
    }
    
    if (error2 < 1)
    {
        m_out << "Rank : SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    Utilities::Date::MyDate tomorrow(19,12,2014);
    rankings.Compute(std::vector<Tournament>(1, tournament), tomorrow);
    
#ifdef _DEBUG
    m_out << rankings << std::endl;
#endif
    
    return true;
}

bool RegressionTest::StaticDataRanking() const
{
    //  Test of static data used in the ranking
    
    m_out << "Interpolator : " ;
    Utilities::Interp::Interpolator & linear = PointsSystemStaticData::GetOWGRInterpolator();
    
    const double refValuesInterpolator[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0.971428571428571,0.914285714285714,0.857142857142857,0.8,0.742857142857142,0.685714285714285,0.628571428571428,0.571428571428571,0.514285714285714,0.457142857142857,0.399999999999999,0.342857142857142,0.285714285714285,0.228571428571428,0.171428571428571,0.114285714285714,0.0571428571428563,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    double errorInterpolator = 0;
    int i = 0;
    for (double x = -2 ; x < 4.0 ; x += 0.1, i++)
    {
        errorInterpolator += std::abs(refValuesInterpolator[i] - linear(x));
#ifdef _DEBUG
        m_out << std::setprecision(15) << linear(x) << "," ;
#endif
    }
    const double tolerance = 1e-10;
    if (errorInterpolator > tolerance)
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    else
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    
    m_out << "Home Rating Value : ";
    std::vector<double> & homeRatingValue = PointsSystemStaticData::GetHomeRatingValues();
    const double refValuesHomeRating[] = {8,7,6,5,4,3,3,3,3,3,3,3,3,3,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    double errorHomeRating = 0.0;
    for (size_t i = 0 ; i < homeRatingValue.size() ; ++i)
    {
        errorHomeRating += std::abs(refValuesHomeRating[i]-homeRatingValue[i]);
#ifdef _DEBUG
        m_out << homeRatingValue[i] << "," ;
#endif
    }
    if (errorHomeRating > tolerance || homeRatingValue.size() != 30)
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    else
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    
    m_out << "World Event Rating Value : ";
    std::vector<double> & worldEventRatingValue = PointsSystemStaticData::GetEventRatingValues();
    const double refValueEventRating[] = {45,37,32,27,24,21,20,19,18,17,16,15,14,13,12,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,10,10,10,10,9,9,9,9,8,8,8,8,8,7,7,7,7,7,7,7,6,6,6,6,6,5,5,5,5,5,4,4,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    double errorEventRating = 0.0;
    for (size_t i = 0 ; i < worldEventRatingValue.size() ; ++i)
    {
        errorEventRating += std::abs(refValueEventRating[i]-worldEventRatingValue[i]);
#ifdef _DEBUG
        m_out << worldEventRatingValue[i] << "," ;
#endif
    }
    if (errorHomeRating > tolerance || worldEventRatingValue.size() != 200)
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    else
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    
    m_out << "Total Rating to 1st point : ";
    Utilities::Interp::Interpolator & totalRatingTo1stPoint = PointsSystemStaticData::GetTotalRatingToFirstPointInterpolator();
    const double refValuestotalRatingTo1stPoints [] = {6,7,7,7,7,7,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,11,11,11,11,11,12,12,12,12,12,13,13,13,13,13,14,14,14,14,14,15,15,15,15,15,16,16,16,16,16,17,17,17,17,17,18,18,18,18,18,19,19,19,19,19,20,20,20,20,20,21,21,21,21,21,22,22,22,22,22,22,22,22,22,22,23,23,23,23,23,24,24,24,24,24,24,24,24,24,24,24,24,24,24,24,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,28,28,28,28,28,28,28,28,28,28,28,28,28,28,28,30,30,30,30,30,30,30,30,30,30,30,30,30,30,30,32,32,32,32,32,32,32,32,32,32,32,32,32,32,32,34,34,34,34,34,34,34,34,34,34,34,34,34,34,34,36,36,36,36,36,36,36,36,36,36,36,36,36,36,36,38,38,38,38,38,38,38,38,38,38,38,38,38,38,38,40,40,40,40,40,40,40,40,40,40,40,40,40,40,40,42,42,42,42,42,42,42,42,42,42,42,42,42,42,42,44,44,44,44,44,44,44,44,44,44,44,44,44,44,44,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,46,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,48,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,52,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,54,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,56,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,60,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,62,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,64,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,66,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,68,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,70,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,72,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,76,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,78,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80,80};
    double errorTotalRatingTo1stPoint = 0.0;
    i = 0;
    for (double d = 0 ; d < 1000 ; ++d, ++i)
    {
#ifdef _DEBUG
        m_out << totalRatingTo1stPoint(d) << "," ;
#endif
        errorTotalRatingTo1stPoint += std::abs(refValuestotalRatingTo1stPoints[i] - totalRatingTo1stPoint(d));
    }
    
    if (errorTotalRatingTo1stPoint > tolerance || totalRatingTo1stPoint.size() != 93)
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    else
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    
    m_out << "Points compared to 1st : ";
    const std::vector<double> & pointsComparedTo1st = PointsSystemStaticData::PointsComparedTo1st();
    const double refValuesPointsComparedTo1st[] = {100,60,40,30,24,20,18,16,15,14,13,12,11,10,9.5,9,8.5,8,7.5,7,6.5,6,5.8,5.6,5.4,5.2,5,4.8,4.6,4.5,4.4,4.3,4.2,4.1,4,3.9,3.8,3.7,3.6,3.5,3.4,3.3,3.2,3.1,3,2.9,2.8,2.7,2.6,2.5,2.4,2.3,2.2,2.1,2,1.9,1.8,1.7,1.6,1.5,1.5,1.5,1.5,1.5,1.5};
    double errorPointsComparedTo1st = 0.0;
    for (size_t i = 0 ; i < pointsComparedTo1st.size() ; ++i)
    {
        errorPointsComparedTo1st += std::abs(pointsComparedTo1st[i] - refValuesPointsComparedTo1st[i]);
#ifdef _DEBUG
        m_out << pointsComparedTo1st[i] << "," ;
#endif
    }
    
    if (errorPointsComparedTo1st > tolerance)
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    else
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    
    return true;
}

bool RegressionTest::MultipleTournamentsSameWeek() const
{
    Tournament pgatourTournament("dummyPGA",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,PGATOUR)), europeantourTournament("dummyEuro",Utilities::Date::MyDate(18,12,2014), std::vector<TourType>(1,EUROPEANTOUR));
    const size_t numPlayers = 200;
    std::vector<Player> players(numPlayers,std::string("")); // empty string is a char*
    for (size_t i = 0 ; i < numPlayers / 2 ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str());
        
        pgatourTournament.AddPlayer(players[i]);
    }
    for (size_t i = numPlayers / 2 ; i < numPlayers ; ++i)
    {
        std::stringstream ss;
        ss << "Player " << i;
        players[i] = Player(ss.str());
        
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
        error += fabs(tournamentPlayersPGA[player].second.Score() - refValues[player]);
#ifdef _DEBUG
        m_out << tournamentPlayersPGA[player].first.Name() << ":" << tournamentPlayersPGA[player].second.Score() << std::endl;
#endif
    }
    for (size_t player = 0 ; player < tournamentPlayersEuro.size() ; ++player)
    {
        error += fabs(tournamentPlayersEuro[player].second.Score() - refValues[player]);
#ifdef _DEBUG
        m_out << tournamentPlayersEuro[player].first.Name() << ":" << tournamentPlayersEuro[player].second.Score() << std::endl;
#endif
    }
    
    if (error < 1)
    {
        m_out << "Score : SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    size_t error2 = 0;
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
        players[player].AddResult(pgatourTournament);
        players[player].AddResult(europeantourTournament);
    }
    
    const size_t rank[] = {76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32,76,97,61,59,90,2,49,30,93,94,10,12,43,50,20,82,31,86,36,67,39,11,71,74,63,44,99,0,98,16,15,53,91,4,81,14,84,25,33,3,83,47,51,6,54,88,5,60,38,95,78,52,87,58,26,68,27,21,48,65,41,96,22,66,24,73,13,9,28,37,18,7,35,89,45,8,57,56,62,17,77,34,55,85,79,70,75,64,23,69,29,72,1,40,42,46,19,80,92,32};
    
    for (size_t player = 0 ; player < players.size() ; ++player)
    {
#ifdef _DEBUG
        m_out << players[player].Results()[0].Position() << ",";
#endif
        error2 += fabs(rank[player] - players[player].Results()[0].Position());
    }
    
    if (error2 < 1)
    {
        m_out << "Rank : SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    Utilities::Date::MyDate tomorrow(19,12,2014);
    std::vector<Tournament> thisWeekTournaments;
    thisWeekTournaments.push_back(pgatourTournament);
    thisWeekTournaments.push_back(europeantourTournament);
    
    rankings.Compute(thisWeekTournaments, tomorrow);
    
#ifdef _DEBUG
    m_out << rankings << std::endl;
#endif
    
    return true;
}

bool RegressionTest::CoSanctionedTournament() const
{
    std::vector<TourType> tourTypes(2);
    tourTypes[0] = PGATOUR;
    tourTypes[1] = CHALLENGETOUR;
    
    Tournament tournament("dummyEuro",Utilities::Date::MyDate(14,01,2015), tourTypes);
    m_out << "CoSanctioned ? ";
    const bool isCoSanctioned = tournament.CoSanctionedEvent();
    if (!isCoSanctioned)
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    else
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    
    m_out << "Ranking points : ";
    Rankings rankings(PointsSystemStaticData::GetOWGRInterpolator());
    RankingPointSystem rankingPtSystem(rankings);
    tournament.SetPointsTo1st(rankingPtSystem);
    const double rankingPoints = tournament.GetPointsTo1st();
    const double refValue = 24.0, tolerance = 1e-15;
    if (std::abs(rankingPoints-refValue) < tolerance)
    {
        m_out << "SUCCEEDED" << std::endl;
    }
    else
    {
        m_out << "FAILED" << std::endl;
        return false;
    }
    
    return true;
}