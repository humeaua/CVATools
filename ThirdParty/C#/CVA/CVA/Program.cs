using System; // for Console
using System.IO; // for File
using System.Linq; // for Select
using NameParser; // for HTML Parser

namespace CVA
{
	class MainClass
	{
		public static void DisplayContents(ref string cChoice)
		{
			Console.WriteLine ("Welcome in the OWGR generator");

			Console.WriteLine ("1- Get files from Internet");
			Console.WriteLine ("2- Parse player files");
			Console.WriteLine ("3- Test HTML Parser");
			Console.WriteLine ("4- CSV File Reader");
			cChoice = Console.ReadLine ();
		}

		public static bool IsFinish()
		{
			Console.WriteLine ("Do you wish to continue ? (Y/N)");
			string cResult = Console.ReadLine ();

			return !(cResult == "y" || cResult == "Y");
		}

		public static void Main (string[] args)
		{
			bool bIsFinished = false;

			while (!bIsFinished) 
			{
				string cChoice = "";
				DisplayContents (ref cChoice);
				if (cChoice == "1") {
					InternetPageReader sInternetPageReader = new CVA.InternetPageReader ();
					DateTime ss = System.DateTime.Now;
					FileParser sFileParser = new CVA.FileParser ();

					for (int i = 1; i <= 2; ++i) {
						string cWebsite = "http://www.officialworldgolfranking.com/rankings/default.sps?region=world&PageCount=" + i;
						string cFileName = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/OfficialWorldGolfRankingHomePage" + i + ".htm";
						sInternetPageReader.ToTextFile (ref cWebsite,
						                                ref cFileName);

						//	Parse file of WorldRanking
						sFileParser.ParseWorldRanking (ref cFileName);
					}
					Console.WriteLine ("Elasped time : " + (System.DateTime.Now - ss));
					ss = DateTime.Now;

					// Do not delete files any more
					string cDirectoryHTM = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/PlayersHTM/";
					Console.WriteLine ("Do you want to delete existing files ?");
					string cDelete = System.Console.ReadLine ();
					if (cDelete == "Y" || cDelete == "y") {
						Console.WriteLine ("Deleting already existing files");
						FileDeleter sFiles = new FileDeleter (ref cDirectoryHTM);
						sFiles.Delete ();
						System.Console.WriteLine ("Deleting done in " + (DateTime.Now - ss));
						ss = System.DateTime.Now;
					}

					string nameprefix = "name=", rankprefix = "&Rank=", totalpoint = "&TotalPt";
					foreach (string c in sFileParser.FutureWebsites) {
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

					Console.WriteLine ("Elapsed time to get all files : " + (DateTime.Now - ss));
					
					bIsFinished = IsFinish ();
				} else if (cChoice == "2") {
					// do something
					Console.WriteLine ("Not yet implemented");
					bIsFinished = true;
				} else if (cChoice == "3") {
					Console.WriteLine ("Test of HTML Parser");
					string cLine = "<b><i>blabla</i>  <u> blibli </u></b> bloblo";
					TextStyle sDefaultStyle = new TextStyle ();
					TextStyle.TextStyleCollection tsc = HTMLParser.ParseHTML (cLine, sDefaultStyle);

					Console.WriteLine (tsc.ToString ());
					TextStyle[] sTextStyleArray = new TextStyle[16];
					tsc.CopyTo (sTextStyleArray);
					for (int i = 0; i < sTextStyleArray.Length; i ++) {
						if (sTextStyleArray [i] != null) {
							Console.WriteLine ("i = " + i + " : ");
							Console.WriteLine (sTextStyleArray [i].ToString ());
						} else {
							Console.WriteLine ("i = " + i + " : null");
						}
					}

					bIsFinished = true;
				} 
				else if (cChoice == "4") 
				{
					string cFileName = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/Golf/Players/Adam_Scott.csv";
					var lines = File.ReadAllLines(cFileName).Select(a => a.Split(';'));
					var csv = from line in lines
						select (from piece in line
						        select piece);

					foreach (var element in csv) 
					{
						foreach (var element2 in element) 
						{
							Console.Write(element2 + " ; ");
						}
						Console.WriteLine("");
					}

					bIsFinished = true;
				}
				else 
				{
					bIsFinished = true;
				}
			}

			Console.WriteLine ("Good bye !");
		}
	}
}
