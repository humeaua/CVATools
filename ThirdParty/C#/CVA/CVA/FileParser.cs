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

		private string ParseBody(ref XmlReader reader)
		{
			//	Method to parse the body of the HTML file
			try
			{
				while (true) 
				{
					if (reader.Read ()) 
					{
						//	The table has 6 attributes
						if (reader.NodeType == XmlNodeType.Element && reader.AttributeCount == 6) {
							//	Check the values of the attributes
							if (reader.GetAttribute (0) != "780" || // width
							    reader.GetAttribute (1) != "0" || // border
						    	reader.GetAttribute (2) != "0" || // cellspacing
						    	reader.GetAttribute (3) != "0" || // cellpadding
							    reader.GetAttribute (4) != "100%" || // height
							    reader.GetAttribute (5) != "#FFFFFF") {
								throw new MyException ("One of the attributes is not correct");
							}
						}
					}
					else 
					{
						//	Reader.Read() has failed : do nothing for now
						return "Reader.Read() has failed";
					}
				}
			}
			catch (Exception excep) {
				throw new MyException ("Exception caught in ParseBody : " + excep);
			}
			return "";
		}

		private void PrintXMLType(ref XmlReader reader)
		{
			//System.IO.StreamWriter fileerror = new System.IO.StreamWriter("/Users/alexhum49/Desktop/OutputError.txt");
			//System.IO.StreamWriter fileoutput = new System.IO.StreamWriter ("/Users/alexhum49/Desktop/OutputType.xml");
			while (true) {
				try {
					if (reader.Read ()) {
						if (reader.NodeType == XmlNodeType.Element &&
							(	reader.Name.ToUpper () == "HEAD" ||
						   		reader.Name.ToUpper () == "SCRIPT" ||
						   		reader.Name.ToUpper () == "LINK" ||
								reader.Name.ToUpper () == "META" ||
								reader.Name.ToUpper() == "NOSCRIPT" ||
								reader.Name.ToUpper() == "TITLE" ||
								reader.Name.ToUpper() == "HTML")) {
							continue;
						}
						if (reader.NodeType == XmlNodeType.EndElement &&
							(	reader.Name.ToUpper () == "HEAD" ||
						   		reader.Name.ToUpper () == "SCRIPT" ||
						   		reader.Name.ToUpper () == "LINK" ||
								reader.Name.ToUpper () == "META"||
								reader.Name.ToUpper() == "NOSCRIPT" ||
								reader.Name.ToUpper() == "TITLE")) {
							continue;
						}
						if (reader.NodeType == XmlNodeType.EndElement && reader.Name.ToUpper() == "HTML")
						{
							//	end of html file
							break;
						}
						if (reader.NodeType == XmlNodeType.Whitespace
						   || reader.NodeType == XmlNodeType.SignificantWhitespace) {
							continue;
						}
						if (reader.NodeType == XmlNodeType.Text && reader.Name == "") {
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
						switch (reader.NodeType) {
						case XmlNodeType.Element:
						{
							switch (reader.Name.ToUpper ()) {
							case "BODY":
								if (reader.AttributeCount == 4)
 								{
									// 4 attributes : leftmargin, topmargin, marginheight, marginwidth 
									//	Check attributes
									if (reader.GetAttribute (0) != "0" || // left margin
										reader.GetAttribute (1) != "0" || // top margin
										reader.GetAttribute (2) != "0" || // margin height
										reader.GetAttribute (3) != "0")   // margin width
									{
										throw new MyException ("One of the attributes is not correct");
									}
									string cError = ParseBody (ref reader);
									if (cError != "")
									{
										throw new Exception(cError);
									}
									break;
								}

							default:
								break;
							}
						}
							break;
						default:	
							//	Do not do anything
							break;
						}
						//	Body has been parsed --> break reading
						//	All the first elements have been parsed by the first conditions checks done at the beginning of the method
						break;
					}
					else 
					{
						//	Reader.Read() has failed
						continue;
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
				catch (MyException excep) {
					// output error
					Console.WriteLine ("MyException Caught {0}", excep);
				}
				catch (Exception excep) {
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
		}

		//	may look at the following website for correct parsing of HTML file
		// 	http://stackoverflow.com/questions/8194155/c-sharp-parse-xml-file
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

