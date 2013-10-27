// Class to delete all files in directory

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
			System.IO.DirectoryInfo downloadedMessageInfo = new System.IO.DirectoryInfo(cDirectoryName);

			foreach (System.IO.FileInfo file in downloadedMessageInfo.GetFiles())
			{
				file.Delete(); 
			}
		}

		private void DeleteAllSubDirectories(ref string cDirectoryName)
		{
			System.IO.DirectoryInfo downloadedMessageInfo = new System.IO.DirectoryInfo(cDirectoryName);

			foreach (System.IO.DirectoryInfo dir in downloadedMessageInfo.GetDirectories())
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

