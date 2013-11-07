using System;
using System.Collections.Generic; // for list

namespace CVA
{
	public class Ranking
	{
		#region Implementation
		List<Player> Rankings;
		#endregion

		public Ranking ()
		{
			Rankings = new List<Player>();
		}

		public Ranking(ref List<Player> Rankings0)
		{
			Rankings = Rankings0;

			Rankings.Sort ();
		}

		public void Print()
		{
			foreach (Player player in Rankings) 
			{
				Console.WriteLine (player.ToString ());
			}
		}
	}
}

