using System;

namespace CVA
{
	public class InternetPageReader
	{
		public InternetPageReader ()
		{}

		public void ToTextFile(ref string cWebsite, ref string cTextFile)
		{
			System.Net.WebClient wc = new System.Net.WebClient ();
			byte[] raw = wc.DownloadData(cWebsite);

			string webData = System.Text.Encoding.UTF8.GetString(raw);

			//	Print in text file 
			System.IO.File.WriteAllText(cTextFile, webData);
		}
	}
}

