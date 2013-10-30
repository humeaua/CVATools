// Class to delete all files in directory
using System.IO; // for DirectorInfo and FileInfo

namespace CVA
{
	public class FileDeleter
	{
		private string cDirectoryName;
		public FileDeleter (ref string cDirectoryName0)
		{
			cDirectoryName = cDirectoryName0;
		}

		private void DeleteAllFiles(ref string cDirectoryName)
		{
			DirectoryInfo downloadedMessageInfo = new DirectoryInfo(cDirectoryName);

			foreach (FileInfo file in downloadedMessageInfo.GetFiles())
			{
				file.Delete(); 
			}
		}

		private void DeleteAllSubDirectories(ref string cDirectoryName)
		{
			DirectoryInfo downloadedMessageInfo = new DirectoryInfo(cDirectoryName);

			foreach (DirectoryInfo dir in downloadedMessageInfo.GetDirectories())
			{
				dir.Delete(true); 
			}
		}

		public void Delete()
		{
			DeleteAllFiles (ref cDirectoryName);
			DeleteAllSubDirectories (ref cDirectoryName);
		}
	}
}

