using System;
using System.Collections.Generic; // for list

namespace CVA
{
	public class Ranking
	{
		#region Implementation
		List<Player> Rankings_;
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

		public List<Player> Rankings
		{
			get
			{
				if (Rankings_ == null)
				{
					Rankings_ = new List<Player>();
				}
				if (Rankings_.Count < 1)
				{
					string cEmptyString = "";
					Rankings_.Add (new Player (ref cEmptyString, ref cEmptyString));
				}
				return Rankings_;
			}
			set
			{
				Rankings_ = value;
			}
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

