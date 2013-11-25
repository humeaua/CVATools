using System;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Xml;
using System.Xml.Schema;

namespace NameParser
{
	/// <summary>
	/// Summary description for HTMLParser.
	/// </summary>
	public class HTMLParser
	{
		public const string RE_HTMLTag = @"\<.*?>";
		public const string RE_QuoteAttributes = @"\<(?<tagName>[a-zA-Z]*) (?<attributeName>[a-zA-Z]*)( )*=( )*(?<attributeValue>[#a-zA-Z0-9]*)?>";
		
		protected static Regex HTMLTagRE;
		protected static Regex QuoteAttributesRE;

		static HTMLParser()
		{
			HTMLTagRE = new Regex(RE_HTMLTag, RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.Singleline);
			QuoteAttributesRE = new Regex(RE_QuoteAttributes, RegexOptions.Compiled | RegexOptions.IgnoreCase | RegexOptions.Singleline | RegexOptions.ExplicitCapture);
		}

		public HTMLParser()
		{}

		public static string QuoteAttributes(ref string input)
		{
			int tagIndex = QuoteAttributesRE.GroupNumberFromName("tagName");
			int nameIndex = QuoteAttributesRE.GroupNumberFromName("attributeName");
			int valueIndex = QuoteAttributesRE.GroupNumberFromName("attributeValue");

			int startAt = 0;

			string val = input;

			while( QuoteAttributesRE.IsMatch(val, startAt) )
			{
				Match m = QuoteAttributesRE.Match(val, startAt);

				string tagName = m.Groups[tagIndex].Value;
				string attributeName = m.Groups[nameIndex].Value;
				string attributeValue = m.Groups[valueIndex].Value;

				if( m.Groups[valueIndex].Length > 0 )
				{
					System.Diagnostics.Trace.WriteLine(attributeName + " " + attributeValue);

					val = QuoteAttributesRE.Replace(val, "<" + tagName + " " + attributeName + "='" + attributeValue + "'>", 1, startAt);
				}

				startAt = m.Index + m.Length + 3;
			}

			return val;
		}


		public static TextStyle.TextStyleCollection ParseHTML(ref string html, ref TextStyle defaultStyle)
		{
			TextStyle.TextStyleCollection tsc = new TextStyle.TextStyleCollection();
			string text = "<html>" + html + "</html>";

			XmlDocument xdf = new XmlDocument();

			xdf.LoadXml(text);

			foreach(XmlNode node in xdf.ChildNodes[0].ChildNodes)
			{
				ParseNode(node, ref defaultStyle, ref tsc);
			}

			return tsc;
		}

		private static void ParseNode(XmlNode node, ref TextStyle defaultStyle, ref TextStyle.TextStyleCollection tsc)
		{
			TextStyle style = new TextStyle(defaultStyle);

			System.Diagnostics.Trace.WriteLine(node.Name);
			System.Diagnostics.Trace.Indent();

			switch(node.Name.ToLower())
			{
				case "font":
					if( node.Attributes != null )
					{
						foreach( XmlAttribute attribute in node.Attributes)
						{
							System.Diagnostics.Trace.WriteLine(attribute.Name + "=" + attribute.Value, "Attribute");

							switch(attribute.Name.ToLower())
							{
								case "color":
									try
									{
										if( attribute.Value[0] != '#' )
											style.ForeColor = Color.FromName(attribute.Value);
										else
											style.ForeColor = Color.FromArgb(
												Int32.Parse(attribute.Value.Substring(1,2), System.Globalization.NumberStyles.HexNumber ), 
												Int32.Parse(attribute.Value.Substring(3,2), System.Globalization.NumberStyles.HexNumber ), 
												Int32.Parse(attribute.Value.Substring(5,2), System.Globalization.NumberStyles.HexNumber )
												);
									}
									catch
									{}
									break;
							}
						}
					}
					break;
				case "b":
				case "strong":
					style.Bold = true;
					break;
				case "i":
				case "em":
					style.Italic = true;
					break;
				case "u":
					style.Underline = true;
					break;
				case "sup":
					style.Superscript = true;
					break;
				case "sub":
					style.Subscript = true;
					break;
			}

			if( node.Name == "#text" )
			{
				TextStyle ts = new TextStyle(style);
				ts.Text = node.Value;
				tsc.Add(ts);
			}

			if( node.HasChildNodes )
			{
				foreach(XmlNode childNode in node.ChildNodes)
				{
					ParseNode(childNode, ref style, ref tsc);
				}
			}

			System.Diagnostics.Trace.Unindent();
			System.Diagnostics.Trace.WriteLine("/" + node.Name );
		}

		public static string RemoveHTMLTags(string input)
		{
			return HTMLTagRE.Replace(input, "");
		}
	}
}
