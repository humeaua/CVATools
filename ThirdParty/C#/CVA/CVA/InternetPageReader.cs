using System.Net; // for Webclient
using System.Text; // For Encoding

namespace CVA
{
	public class InternetPageReader
	{
		public InternetPageReader ()
		{}

		public void ToTextFile(ref string cWebsite, ref string cTextFile)
		{
			WebClient wc = new System.Net.WebClient ();
			byte[] raw = wc.DownloadData(cWebsite);

			string webData = Encoding.UTF8.GetString(raw);

			//	Print in text file 
			System.IO.File.WriteAllText(cTextFile, webData);
		}
	}
}

