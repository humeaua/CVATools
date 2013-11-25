using System.Collections.Generic; // for list
using System; // for console
using System.IO; // for file
using System.Linq; // for select

namespace CVA
{
	public class Player
	{
		#region Implementation
		private string cFirstName, cLastName;
		private int iRanking;
		private int iNTournamentsPlayed;
		private double dTotalPoints;

		private double dAverage;
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
			iRanking = 0;
			iNTournamentsPlayed = 0;
			dTotalPoints = 0.0;
			LoadFromCSVFile (ref cFileName);
		}

		public void LoadFromCSVFile(ref string cFileName)
		{
			// to do
			// copy the existing c++ file
			var lines = File.ReadAllLines(cFileName).Select(a => a.Split(';'));
			var csv = from line in lines
				select (from piece in line
				        select piece);

			foreach (string[] element in csv) 
			{
				if (element.Length != 4) 
				{
					throw new MyException ("Player::LoadFromCSVFile : Element does not have the correct length when reading from CSV file");
				}
				PlayerResult sPlayerResult = new PlayerResult();

				sPlayerResult.Date = new DateTime (Convert.ToInt32(element  [2]), 1, 1);
				sPlayerResult.Date.AddDays (Convert.ToInt32(element [3]) * 7);
				sPlayerResult.Name = element [0];
				sPlayerResult.Point = Convert.ToDouble(element [4]);
			
				sResults.Add (sPlayerResult);

				dTotalPoints += sPlayerResult.Point;
				iNTournamentsPlayed += 1;
			}
		}

		public double Average0()
		{
			if (iNTournamentsPlayed <= 40)
				dAverage = dTotalPoints / 40.0;
			else if (iNTournamentsPlayed >= 52)
				dAverage = dTotalPoints / 52.0;
			else
				dAverage = dTotalPoints / iNTournamentsPlayed;
			return dAverage;
		}

		public double Average
		{
			get
			{
				return dAverage;
			}
		}

		public void PrintName()
		{
			Console.WriteLine ("{0} {1} : {2}", cFirstName, cLastName, Average0 ());
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

		public int Ranking
		{
			get
			{ 
				return iRanking;
			}
			set
			{
				iRanking = value; 
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
			return sLeft.Average < sRight.Average;
		}

		public static bool operator > (Player sLeft, Player sRight)
		{
			return sLeft.Average > sRight.Average;
		}

		public bool HasPlayed(ref Tournament sTournament)
		{
			return sTournament.Results.ContainsKey(new Tuple<string,string>(FirstName, LastName));
		}
	}
}

