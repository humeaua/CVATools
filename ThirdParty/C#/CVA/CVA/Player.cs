using System.Collections.Generic; // for list
using System; // for console

namespace CVA
{
	public class Player
	{
		#region Implementation
		private string cFirstName, cLastName;
		private int iRanking;
		private int iNTournamentsPlayed;
		private double dTotalPoints;

		private List<PlayerResult> sResults;
		#endregion

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

		public string FirstName
		{
			get
			{
				return cFirstName;
			}
			set
			{
				cFirstName = value;
			}
		}

		public string LastName
		{
			get 
			{
				return cLastName;
			}
			set
			{
				cLastName = value;
			}
		}

		public void Print()
		{
			Console.WriteLine ("{0} {1}", FirstName, LastName);
			foreach (PlayerResult sTournament in sResults)
			{
				Console.WriteLine("{0} {1}", sTournament.Name, sTournament.Point);
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

		public bool HasPlayed(ref Tournament sTournament)
		{
			return sTournament.Results.ContainsKey(new Tuple<string,string>(FirstName, LastName));
		}
	}
}

