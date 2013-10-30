using System.Collections.Generic; // for list
using System; // for console

namespace CVA
{
	public class Player
	{
		private string cFirstName, cLastName;
		private int iRanking;
		private int iNTournamentsPlayed;
		private double dTotalPoints;

		private List<PlayerResult> sResults;

		// Constructors
		public Player (ref string cFirstName0, ref string cLastName0)
		{
			cFirstName = cFirstName0;
			cLastName = cLastName0;
			iRanking = 0;
			iNTournamentsPlayed = 0;
			dTotalPoints = 0.0;
		}

		public Player (ref string cFileName)
		{
			LoadFromFile (ref cFileName);
		}

		public void LoadFromFile(ref string cFileName)
		{
			// to do
			// copy the existing c++ file
		}

		public double Average()
		{
			if (iNTournamentsPlayed <= 40)
				return dTotalPoints / 40.0;
			else if (iNTournamentsPlayed >= 52)
				return dTotalPoints / 52.0;
			else
				return dTotalPoints / iNTournamentsPlayed;
		}

		public void PrintName()
		{
			Console.WriteLine ("{0} {1} : {2}", cFirstName, cLastName, Average ());
		}

		public void Print()
		{
			Console.WriteLine ("{0} {1}", cFirstName, cLastName);
			foreach (PlayerResult sTournament in sResults)
			{
				Console.WriteLine("{0} {1}", sTournament.GetName(), sTournament.GetPoint());
			}
		}

		public static bool operator < (Player sLeft, Player sRight)
		{
			return sLeft.Average() < sRight.Average();
		}

		public static bool operator > (Player sLeft, Player sRight)
		{
			return sLeft.Average() > sRight.Average();
		}
	}
}

