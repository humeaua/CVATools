using System.Collections.Generic; //	For list
using System.Xml; // for XML Reader
using System.IO; // for file
using System; // for console 

namespace CVA
{
	public class FileParser
	{
		#region Implementation
		private List<string> FutureWebsiteToBeCalled;
		#endregion

		public FileParser ()
		{
			FutureWebsiteToBeCalled = new List<string> ();
		}

		public List<string> FutureWebsites
		{
			get
			{ 
				return FutureWebsiteToBeCalled;
			}
			set
			{ 
				FutureWebsiteToBeCalled = value;
			}
		}

		public void ParseWorldRanking(ref string cFilePath)
		{
			string cSearchedString = "/players/bio.sps?";
			string cBegin = "href=";
			string cWebsiteName = "http://www.officialworldgolfranking.com/";
			foreach (var line in System.IO.File.ReadAllLines(cFilePath))
			{
				if (line.Contains (cSearchedString)) 
				{
					string cLine = line;
					int iFirst = cLine.IndexOf (cBegin) + cBegin.Length + 1;
					int iLast = cLine.Length - 1;

					string str = cLine.Substring (iFirst, iLast - iFirst);

					FutureWebsiteToBeCalled.Add (cWebsiteName + str);
				}
			}
			System.Console.WriteLine ("Parse World Ranking file done");
		}

		private void ParseNode()
		{
		}

		private void ParseBody(ref XmlReader reader)
		{
		}

		private void PrintXMLType(ref XmlReader reader)
		{
			//System.IO.StreamWriter fileerror = new System.IO.StreamWriter("/Users/alexhum49/Desktop/OutputError.txt");
			//System.IO.StreamWriter fileoutput = new System.IO.StreamWriter ("/Users/alexhum49/Desktop/OutputType.xml");
			try
			{
				while (reader.Read())					
				{
					if (reader.NodeType == XmlNodeType.Element &&
						 (reader.Name.ToUpper() == "HEAD" || 
							reader.Name.ToUpper() == "SCRIPT" || 
							reader.Name.ToUpper() == "LINK" ||
							reader.Name.ToUpper() == "META"))
					{
						continue;
					}
					if (reader.NodeType == XmlNodeType.EndElement && 
						(reader.Name.ToUpper() == "HEAD" || 
							reader.Name.ToUpper() == "SCRIPT" || 
							reader.Name.ToUpper() == "LINK" ||
							reader.Name.ToUpper() == "META"))
					{
						continue;
					}
					if (reader.NodeType == XmlNodeType.Whitespace
						 || reader.NodeType == XmlNodeType.SignificantWhitespace)
					{
						continue;
					}
					if (reader.NodeType == XmlNodeType.Text && reader.Name == "")
					{
						continue;
					}
				/*switch (reader.NodeType) 
					{
					case XmlNodeType.Element: // The node is an element.
						fileoutput.Write("<" + reader.Name);						
						while (reader.MoveToNextAttribue())
							// Read the attributes.
							fileoutput.Write(" " + reader.Name + "='" + reader.Value + "'");
						fileoutput.WriteLine(">");
						break;
					case XmlNodeType.Text: //Display the text in each element.
						fileoutput.WriteLine (reader.Value);
						break;
					case XmlNodeType. EndElement: //Display the end of the element.
						fileoutput.Write("</" + reader.Name);
						fileoutput.WriteLine(">");
						break;
					}*/
					switch (reader.NodeType)
					{
					case XmlNodeType.Element:
						switch (reader.Name.ToUpper()){
					case "BODY":
							if (reader.AttributeCount == 4)
							// 4 attributes : leftmargin, topmargin, marginheight, marginwidth 
							{
								if (reader.GetAttribute(0) != "0" || reader.GetAttribute(1) != "0")
								{									{
									throw new MyException("Not correct attribute");
								}
							}
							ParseBody(ref reader);
							break;
							}

						default:
							break;
						}
					break;
					default:	
						//	Do not do anything
						break;
					}
				}

					/*switch (reader.NodeType) {
							case XmlNodeType.Attribute:
							fileoutput.WriteLine ("Attribute");
								break;
							case XmlNodeType.CDATA:
							fileoutput.WriteLine ("CDATA");
								break;
							case XmlNodeType.Comment:
							fileoutput.WriteLine ("Comment");
								break;
							case XmlNodeType.Document:
							fileoutput.WriteLine ("Document");
								break;
							case XmlNodeType.DocumentFragment:
							fileoutput.WriteLine ("DocumentFragment");
								break;
							case XmlNodeType.DocumentType:
							fileoutput.WriteLine ("DocumentType");
								break;
							case XmlNodeType.Element:
							fileoutput.WriteLine ("Element");
								break;
							case XmlNodeType.EndElement:
							fileoutput.WriteLine ("EndElement");
								break;
							case XmlNodeType.EndEntity:
							fileoutput.WriteLine ("EndElement");
								break;
							case XmlNodeType.Entity:
							fileoutput.WriteLine ("Entity");
								break;
							case XmlNodeType.EntityReference:
							fileoutput.WriteLine ("EntityReference");
								break;
							case XmlNodeType.None:
							fileoutput.WriteLine ("None");
								break;
							case XmlNodeType.Notation:
							fileoutput.WriteLine ("Notation");
								break;
							case XmlNodeType.ProcessingInstruction:
							fileoutput.WriteLine ("ProcessingInstruction");
								break;
							case XmlNodeType.SignificantWhitespace:
							fileoutput.WriteLine ("SignificantWhitespace");
								break;
							case XmlNodeType.Text:
							fileoutput.WriteLine ("Text");
								break;
							case XmlNodeType.Whitespace:
							fileoutput.WriteLine ("Whitespace");
								break;
							case XmlNodeType.XmlDeclaration:
							fileoutput.WriteLine ("XmlDeclaration");
								break;
							default:
								throw new MyException ("Should not get there");

							}
				}*/
						
			}
			
			catch (Exception excep)
			{
				//try
				//{
					//fileoutput.WriteLine("Exception caught");
				//	fileerror.WriteLine("Exception caught {0}", excep);
				//}
				//catch (System.StackOverflowException e) {
				//	Console.WriteLine ("Process terminated due to StackOverFlow Exception {0} ", e);
				//	break;
				//}
			}
		}

		public void ParsePlayerNew(ref string cFilePath)
		{
			// 	Read file into string
			string cHTMLString = File.ReadAllText (cFilePath);

			/*//	Define settings for XML Writer to Tournament Element
			XmlWriterSettings ws = new XmlWriterSettings();
			ws.Indent = true;*/

			// 	Create an XML Reader 
			//using (XmlReader reader = XmlReader.Create (new StringReader(cHTMLString)) )
			{
				XmlReader reader  = XmlReader.Create (new StringReader (cHTMLString));
				//	Open body
				PrintXMLType (ref reader);
				// 	Open big table 780 * 1218
				//	Open table 780 * 1045

				//	Open central table 485 * 1085

				//	Open centrale table 465 * 1035

				// 	Open table 465 * 728

				//	Readlines one by one
			}
		}

		public void ParsePlayer(ref string cFilePath)
		{
			string cSearchedString = "/events/events_scorecard.sps?EventID";
			string cBegin = @"""newsdate"">";
			//string cEnd = "</a>&nbsp;</td>";
			foreach (var line in System.IO.File.ReadAllLines(cFilePath)) 
			{
				if (line.Contains (cSearchedString)) 
				{
					int iFirst = line.IndexOf (cBegin) + cBegin.Length + 1;
					int iLast = line.IndexOf (cBegin);

					string cTournamentName = line.Substring (iFirst, iLast - iFirst);

				}
			}
			/*
 static void Main(string[] args) {
        String xml = @"
            <transactions>
                <transaction name=""Fred"" amount=""5,20"" />
                <transaction name=""John"" amount=""10,00"" />
                <transaction name=""Fred"" amount=""3,00"" />
            </transactions>";

        XDocument xmlDocument = XDocument.Parse(xml);

        var query = from x in xmlDocument.Descendants("transaction")
                    group x by x.Attribute("name").Value into g
                    select new { Name = g.Key, Amount = g.Sum(t => Decimal.Parse(t.Attribute("amount").Value)) };

        foreach (var item in query) {
            Console.WriteLine("Name: {0}; Amount: {1:C};", item.Name, item.Amount);
        }
    }
			 */
		}
	}
}

