namespace CVA
{
	class MainClass
	{
		public static void Main (string[] args)
		{
			System.Console.WriteLine ("Welcome !");
			CVA.InternetPageReader sInternetPageReader = new CVA.InternetPageReader ();
			string cWebsite = "http://www.officialworldgolfranking.com/home/default.sps";
			string cFileName = "/Users/alexhum49/Documents/Workspace/CVA/CVATools/Input/OfficialWorldGolfRankingHomePage.txt";
			sInternetPageReader.ToTextFile (ref cWebsite,
			                                ref cFileName);
			System.Console.WriteLine ("Good bye !");
		}
	}
}
