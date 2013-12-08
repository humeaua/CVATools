using System;
using System.Collections.Generic;
using System.Xml;
using System.Text;


namespace CVA
{

	/*
	Purpose of this file : 

We would like to create xml files for tournaments player have played in 
The base XML file is done this way 

<h1>PLayerName</h1>
<form>
    <tournament>
        <name>TournamentName1</name>
        <week>Week1</week>
        <year>Year1</year>
        <result>Result1</result>
        <points>Points1</points>
    </tournament>
    <tournament>
        <name>TournamentName2</name>
        <week>Week2</week>
        <year>Year2</year>
        <result>Result2</result>
        <points>Points2</points>
    </tournament>
    ...
</form>
	*/
	public interface IElement
	{
		string RenderStart();
		string RenderEnd();
		string Render();
		IList<IElement> Children { get; }
		void LoadFromXML(XmlReader reader);
	}  // eo interface IElement

	public abstract class Element : IElement
	{
		List<IElement> children_ = new List<IElement>();

		public IList<IElement> Children { get { return children_; } }

		public string Render()
		{
			StringBuilder builder = new StringBuilder(RenderStart());
			foreach(IElement e in children_)
				builder.Append(e.Render());
			builder.Append(RenderEnd());
			return builder.ToString();
		}

		public abstract string RenderStart ();
		public abstract string RenderEnd ();
		public abstract void LoadFromXML (XmlReader reader);

	}  // eo class Element

	public class TournamentElement : Element
	{
		public override string RenderStart()
		{
			StringBuilder builder = new StringBuilder();
			builder.Append("<tournament legend=\"")
				.Append("\">");
			return builder.ToString();
		}

		public override string RenderEnd()
		{
			return ("</tournament>");
		}

		public string Legend {get; set; }
		public string Week{ get; set; }
		public string Year{ get; set; }
		public string Result{ get; set; }
		public string Points{ get; set;}

		public override void LoadFromXML(XmlReader reader)
		{
			Legend = reader.GetAttribute("legend");
			Week = reader.GetAttribute ("week");
			Year = reader.GetAttribute ("year");
			Result = reader.GetAttribute ("result");
			Points = reader.GetAttribute ("points");
		} // eo LoadFromXml
	}  // eo class Tournament
}

