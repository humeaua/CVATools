namespace CVA
{
	class MainClass
	{
		public static void DisplayContents(ref string cChoice)
		{
			System.Console.WriteLine ("Welcome in the OWGR generator");

			System.Console.WriteLine ("1- Get new ranking from Internet");

			cChoice = System.Console.ReadLine ();
		}

		public static bool IsFinish()
		{
			System.Console.WriteLine ("Do you wish to continue ? (Y/N)");
			string cResult = System.Console.ReadLine ();

			return !(cResult == "y" || cResult == "Y");
		}

		public static void Main (string[] args)
		{
			bool bIsFinished = false;

			while (!bIsFinished) 
			{
				string cChoice = "";
				CVA.MainClass.DisplayContents (ref cChoice);
				if (cChoice == "1") {
					CVA.InternetPageReader sInternetPageReader = new CVA.InternetPageReader ();
					string cWebsite = "http://www.officialworldgolfranking.com/rankings/default.sps";
					string cFileName = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/OfficialWorldGolfRankingHomePage.htm";
					sInternetPageReader.ToTextFile (ref cWebsite,
					                                ref cFileName);

					//	Parse file of WorldRanking
					//System.Diagnostics.Stopwatch ss = new System.Diagnostics.Stopwatch { };
					System.DateTime ss = System.DateTime.Now;

					CVA.FileParser sFileParser = new CVA.FileParser ();
					sFileParser.ParseWorldRanking (ref cFileName);
					System.Console.WriteLine ("Elasped time : " + (System.DateTime.Now - ss));
					ss = System.DateTime.Now;

					// Do not delete files any more
					string cDirectoryHTM = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/PlayersHTM/";
					//if (false) {
					//	System.Console.WriteLine ("Deleting already existing files");
					//	CVA.FileDeleter sFiles = new CVA.FileDeleter (ref cDirectoryHTM);
					//	sFiles.Delete ();
					//	System.Console.WriteLine ("Deleting done in " + (System.DateTime.Now - ss));
					//	ss = System.DateTime.Now;
					//}

					string nameprefix = "name=", rankprefix = "&Rank=", totalpoint = "&TotalPt";
					foreach (string c in sFileParser.FutureWebsiteToBeCalled) {
						// Find the player name to have the correct file name before parsing it

						int iFirstNamePlayer = c.IndexOf (nameprefix) + nameprefix.Length,
						iRankPlayerFirst = c.IndexOf (rankprefix),
						iRankPlayerLast = iRankPlayerFirst + rankprefix.Length,
						iTotalPointFirst = c.IndexOf (totalpoint);

						string cFutureWebsiteToBeCalled = c;
						string cFileNamePlayer = c.Substring (iFirstNamePlayer, iRankPlayerFirst - iFirstNamePlayer) + "_" + c.Substring (iRankPlayerLast, iTotalPointFirst - iRankPlayerLast);
						string cPathToFileNamePlayer = cDirectoryHTM + cFileNamePlayer + ".htm";
						sInternetPageReader.ToTextFile (ref cFutureWebsiteToBeCalled, ref cPathToFileNamePlayer);
					}

					System.Console.WriteLine ("Elapsed time to get all files : " + (System.DateTime.Now - ss));
					
					bIsFinished = CVA.MainClass.IsFinish ();
				} 
				else 
				{
					bIsFinished = true;
				}
			}
			System.Console.WriteLine ("Good bye !");

		}
	}
}
