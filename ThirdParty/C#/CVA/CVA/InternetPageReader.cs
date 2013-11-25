using System.Net; // for Webclient
using System.Text; // For Encoding
using System.IO; // for File

namespace CVA
{
	public class InternetPageReader
	{
		public InternetPageReader ()
		{}

		public void ToTextFile(ref string cWebsite, ref string cTextFile)
		{
			WebClient wc = new WebClient ();
			byte[] raw = wc.DownloadData(cWebsite);

			string webData = Encoding.UTF8.GetString(raw);

			//	Print in text file 
			File.WriteAllText(cTextFile, webData);
		}
	}
}

