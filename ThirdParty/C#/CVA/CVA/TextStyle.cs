using System;
using System.Collections;
using System.Drawing;

namespace NameParser
{
	/// <summary>
	/// Summary description for TextStyle.
	/// </summary>
	public class TextStyle
	{
		#region Implementation Data
		private Color foreColor;
		private string text;
		private bool bold;
		private bool italic;
		private bool underline;
		private bool superscript;
		private bool subscript;
		#endregion
        
		#region Constructors
		public TextStyle()
		{
			ForeColor = Color.Empty;
			Text = "";
			bold = false;
			italic = false;
			underline = false;
			superscript = false;
			subscript = false;
		}

		public TextStyle(TextStyle copy)
		{
			ForeColor = copy.ForeColor;
			Text = copy.Text;
			bold = copy.bold;
			italic = copy.italic;
			underline = copy.underline;
			superscript = copy.superscript;
			subscript = copy.subscript;
		}
		#endregion

		#region Properties
		public Color ForeColor
		{
			get
			{
				return foreColor;
			}
			set
			{
				foreColor = value;
			}
		}

		public string Text
		{
			get
			{
				return text;
			}
			set
			{
				text = value;
			}
		}

		public bool Bold
		{
			get
			{
				return bold;
			}
			set
			{
				bold = value;
			}
		}

		public bool Italic
		{
			get
			{
				return italic;
			}
			set
			{
				italic = value;
			}
		}

		public bool Underline
		{
			get
			{
				return underline;
			}
			set
			{
				underline = value;
			}
		}

		public bool Superscript
		{
			get
			{
				return superscript;
			}
			set
			{
				if( value == true )
					subscript = false;

				superscript = value;		
			}
		}

		public bool Subscript
		{
			get
			{
				return subscript;
			}
			set
			{
				if( value == true )
					superscript = false;

				subscript = value;
			}
		}
		#endregion Properties

		#region Methods
		public override string ToString()
		{
			System.Text.StringBuilder sb = new System.Text.StringBuilder();

			sb.Append("Text: " + this.Text);
			sb.Append("\r\nForeColor: " + this.ForeColor);
			sb.Append("\r\nFontStyle: ");
			if( this.Bold )
				sb.Append("Bold ");
			if( this.Italic)
				sb.Append("Italic ");
			if( this.Underline )
				sb.Append("Underline ");
			if( this.Superscript )
				sb.Append("Superscript ");
			if( this.Subscript )
				sb.Append("Subscript ");

			return sb.ToString();
		}	
		#endregion

		#region Interfaces
		/// <summary>
		///		Supports type-safe iteration over a <see cref="TextStyleCollection"/>.
		/// </summary>
		public interface ITextStyleCollectionEnumerator
		{
			/// <summary>
			///		Gets the current element in the collection.
			/// </summary>
			TextStyle Current {get;}

			/// <summary>
			///		Advances the enumerator to the next element in the collection.
			/// </summary>
			/// <exception cref="InvalidOperationException">
			///		The collection was modified after the enumerator was created.
			/// </exception>
			/// <returns>
			///		<c>true</c> if the enumerator was successfully advanced to the next element; 
			///		<c>false</c> if the enumerator has passed the end of the collection.
			/// </returns>
			bool MoveNext();

			/// <summary>
			///		Sets the enumerator to its initial position, before the first element in the collection.
			/// </summary>
			void Reset();
		}
		#endregion

		/// <summary>
		///		A strongly-typed collection of <see cref="TextStyle"/> objects.
		/// </summary>
		[Serializable]
		public class TextStyleCollection : ICollection, IList, IEnumerable
		{
			private const int DEFAULT_CAPACITY = 16;

		#region Implementation (data)
			private TextStyle[] m_array;
			private int m_count = 0;
			private int m_version = 0;
		#endregion
	
        #region Static Wrappers
			/// <summary>
			///		Creates a synchronized (thread-safe) wrapper for a 
			///     <c>TextStyleCollection</c> instance.
			/// </summary>
			/// <returns>
			///     An <c>TextStyleCollection</c> wrapper that is synchronized (thread-safe).
			/// </returns>
			public static TextStyleCollection Synchronized(TextStyleCollection list)
			{
				if(list==null)
					throw new ArgumentNullException("list");
				return new SyncTextStyleCollection(list);
			}
        
			/// <summary>
			///		Creates a read-only wrapper for a 
			///     <c>TextStyleCollection</c> instance.
			/// </summary>
			/// <returns>
			///     An <c>TextStyleCollection</c> wrapper that is read-only.
			/// </returns>
			public static TextStyleCollection ReadOnly(TextStyleCollection list)
			{
				if(list==null)
					throw new ArgumentNullException("list");
				return new ReadOnlyTextStyleCollection(list);
			}
        #endregion

	    #region Construction
			/// <summary>
			///		Initializes a new instance of the <c>TextStyleCollection</c> class
			///		that is empty and has the default initial capacity.
			/// </summary>
			public TextStyleCollection()
			{
				m_array = new TextStyle[DEFAULT_CAPACITY];
			}
		
			/// <summary>
			///		Initializes a new instance of the <c>TextStyleCollection</c> class
			///		that has the specified initial capacity.
			/// </summary>
			/// <param name="capacity">
			///		The number of elements that the new <c>TextStyleCollection</c> is initially capable of storing.
			///	</param>
			public TextStyleCollection(int capacity)
			{
				m_array = new TextStyle[capacity];
			}

			/// <summary>
			///		Initializes a new instance of the <c>TextStyleCollection</c> class
			///		that contains elements copied from the specified <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="c">The <c>TextStyleCollection</c> whose elements are copied to the new collection.</param>
			public TextStyleCollection(TextStyleCollection c)
			{
				m_array = new TextStyle[c.Count];
				AddRange(c);
			}

			/// <summary>
			///		Initializes a new instance of the <c>TextStyleCollection</c> class
			///		that contains elements copied from the specified <see cref="TextStyle"/> array.
			/// </summary>
			/// <param name="a">The <see cref="TextStyle"/> array whose elements are copied to the new list.</param>
			public TextStyleCollection(TextStyle[] a)
			{
				m_array = new TextStyle[a.Length];
				AddRange(a);
			}
		#endregion
		
		#region Operations (type-safe ICollection)
			/// <summary>
			///		Gets the number of elements actually contained in the <c>TextStyleCollection</c>.
			/// </summary>
			public virtual int Count
			{
				get { return m_count; }
			}

			/// <summary>
			///		Copies the entire <c>TextStyleCollection</c> to a one-dimensional
			///		string array.
			/// </summary>
			/// <param name="array">The one-dimensional <see cref="TextStyle"/> array to copy to.</param>
			public virtual void CopyTo(TextStyle[] array)
			{
				this.CopyTo(array, 0);
			}

			/// <summary>
			///		Copies the entire <c>TextStyleCollection</c> to a one-dimensional
			///		<see cref="TextStyle"/> array, starting at the specified index of the target array.
			/// </summary>
			/// <param name="array">The one-dimensional <see cref="TextStyle"/> array to copy to.</param>
			/// <param name="start">The zero-based index in <paramref name="array"/> at which copying begins.</param>
			public virtual void CopyTo(TextStyle[] array, int start)
			{
				if (m_count > array.GetUpperBound(0) + 1 - start)
					throw new System.ArgumentException("Destination array was not long enough.");
			
				Array.Copy(m_array, start, array, 0, m_count); 
			}

			/// <summary>
			///		Gets a value indicating whether access to the collection is synchronized (thread-safe).
			/// </summary>
			/// <returns>true if access to the ICollection is synchronized (thread-safe); otherwise, false.</returns>
			public virtual bool IsSynchronized
			{
				get { return m_array.IsSynchronized; }
			}

			/// <summary>
			///		Gets an object that can be used to synchronize access to the collection.
			/// </summary>
			public virtual object SyncRoot
			{
				get { return m_array.SyncRoot; }
			}
		#endregion
		
		#region Operations (type-safe IList)
			/// <summary>
			///		Gets or sets the <see cref="TextStyle"/> at the specified index.
			/// </summary>
			/// <param name="index">The zero-based index of the element to get or set.</param>
			/// <exception cref="ArgumentOutOfRangeException">
			///		<para><paramref name="index"/> is less than zero</para>
			///		<para>-or-</para>
			///		<para><paramref name="index"/> is equal to or greater than <see cref="TextStyleCollection.Count"/>.</para>
			/// </exception>
			public virtual TextStyle this[int index]
			{
				get
				{
					ValidateIndex(index); // throws
					return m_array[index]; 
				}
				set
				{
					ValidateIndex(index); // throws
					++m_version; 
					m_array[index] = value; 
				}
			}

			/// <summary>
			///		Adds a <see cref="TextStyle"/> to the end of the <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="item">The <see cref="TextStyle"/> to be added to the end of the <c>TextStyleCollection</c>.</param>
			/// <returns>The index at which the value has been added.</returns>
			public virtual int Add(TextStyle item)
			{
				++m_version;
			
				Grow();

				m_array[m_count] = item;
				return m_count++;
			}
		
			/// <summary>
			///		Removes all elements from the <c>TextStyleCollection</c>.
			/// </summary>
			public virtual void Clear()
			{
				++m_version;
				m_array = new TextStyle[DEFAULT_CAPACITY];
				m_count = 0;
			}

			/// <summary>
			///		Determines whether a given <see cref="TextStyle"/> is in the <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="item">The <see cref="TextStyle"/> to check for.</param>
			/// <returns><c>true</c> if <paramref name="item"/> is found in the <c>TextStyleCollection</c>; otherwise, <c>false</c>.</returns>
			public virtual bool Contains(TextStyle item)
			{
				for (int i=0; i != m_count; ++i)
					if (m_array[i].Equals(item))
						return true;
				return false;
			}

			/// <summary>
			///		Returns the zero-based index of the first occurrence of a <see cref="TextStyle"/>
			///		in the <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="item">The <see cref="TextStyle"/> to locate in the <c>TextStyleCollection</c>.</param>
			/// <returns>
			///		The zero-based index of the first occurrence of <paramref name="item"/> 
			///		in the entire <c>TextStyleCollection</c>, if found; otherwise, -1.
			///	</returns>
			public virtual int IndexOf(TextStyle item)
			{
				for (int i=0; i != m_count; ++i)
					if (m_array[i].Equals(item))
						return i;
				return -1;
			}

			/// <summary>
			///		Inserts an element into the <c>TextStyleCollection</c> at the specified index.
			/// </summary>
			/// <param name="index">The zero-based index at which <paramref name="item"/> should be inserted.</param>
			/// <param name="item">The <see cref="TextStyle"/> to insert.</param>
			/// <exception cref="ArgumentOutOfRangeException">
			///		<para><paramref name="index"/> is less than zero</para>
			///		<para>-or-</para>
			///		<para><paramref name="index"/> is equal to or greater than <see cref="TextStyleCollection.Count"/>.</para>
			/// </exception>
			public virtual void Insert(int index, TextStyle item)
			{
				ValidateIndex(index, true); // throws
				++m_version;
			
				Grow();

				for (int i=m_count; i > index; --i)
					m_array[i] = m_array[i-1];

				m_array[index] = item;
				m_count++;
			}

			/// <summary>
			///		Removes the first occurrence of a specific <see cref="TextStyle"/> from the <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="item">The <see cref="TextStyle"/> to remove from the <c>TextStyleCollection</c>.</param>
			/// <exception cref="ArgumentException">
			///		The specified <see cref="TextStyle"/> was not found in the <c>TextStyleCollection</c>.
			/// </exception>
			public virtual void Remove(TextStyle item)
			{		   
				int i = IndexOf(item);
				if (i < 0)
					throw new System.ArgumentException("Cannot remove the specified item because it was not found in the specified Collection.");
			
				++m_version;
				RemoveAt(i);
			}

			/// <summary>
			///		Removes the element at the specified index of the <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="index">The zero-based index of the element to remove.</param>
			/// <exception cref="ArgumentOutOfRangeException">
			///		<para><paramref name="index"/> is less than zero</para>
			///		<para>-or-</para>
			///		<para><paramref name="index"/> is equal to or greater than <see cref="TextStyleCollection.Count"/>.</para>
			/// </exception>
			public virtual void RemoveAt(int index)
			{
				ValidateIndex(index); // throws
				++m_version;
			
				m_count--;
				for (int i=index; i != m_count; ++i)
					m_array[i] = m_array[i+1];

				Trim();
			}

			/// <summary>
			///		Gets a value indicating whether the collection has a fixed size.
			/// </summary>
			/// <value>true if the collection has a fixed size; otherwise, false. The default is false</value>
			public virtual bool IsFixedSize
			{
				get { return false; }
			}

			/// <summary>
			///		gets a value indicating whether the IList is read-only.
			/// </summary>
			/// <value>true if the collection is read-only; otherwise, false. The default is false</value>
			public virtual bool IsReadOnly
			{
				get { return false; }
			}
		#endregion

		#region Operations (type-safe IEnumerable)
		
			/// <summary>
			///		Returns an enumerator that can iterate through the <c>TextStyleCollection</c>.
			/// </summary>
			/// <returns>An <see cref="Enumerator"/> for the entire <c>TextStyleCollection</c>.</returns>
			public virtual ITextStyleCollectionEnumerator GetEnumerator()
			{
				return new Enumerator(this);
			}
		#endregion

		#region Public helpers (just to mimic some nice features of ArrayList)
		
			/// <summary>
			///		Gets or sets the number of elements the <c>TextStyleCollection</c> can contain.
			/// </summary>
			public virtual int Capacity
			{
				get { return m_array.Length; }
			
				set
				{
					++m_version;

					if (value < m_count)
						value = m_count;

					if (value != Capacity)
					{
						TextStyle[] temp = new TextStyle[value];
						Array.Copy(m_array, temp, m_array.Length);
						m_array = temp;
					}
				}
			}

			/// <summary>
			///		Adds the elements of another <c>TextStyleCollection</c> to the current <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="x">The <c>TextStyleCollection</c> whose elements should be added to the end of the current <c>TextStyleCollection</c>.</param>
			/// <returns>The new <see cref="TextStyleCollection.Count"/> of the <c>TextStyleCollection</c>.</returns>
			public virtual int AddRange(TextStyleCollection x)
			{
				++m_version;

				Grow(x.Count);
			
				Array.Copy(x.m_array, 0, m_array, m_count, x.Count);
				m_count += x.Count;

				return m_count;
			}

			/// <summary>
			///		Adds the elements of a <see cref="TextStyle"/> array to the current <c>TextStyleCollection</c>.
			/// </summary>
			/// <param name="x">The <see cref="TextStyle"/> array whose elements should be added to the end of the <c>TextStyleCollection</c>.</param>
			/// <returns>The new <see cref="TextStyleCollection.Count"/> of the <c>TextStyleCollection</c>.</returns>
			public virtual int AddRange(TextStyle[] x)
			{
				++m_version;
			
				Grow(x.Length);

				Array.Copy(x, 0, m_array, m_count, x.Length);
				m_count += x.Length;

				return m_count;
			}

		#endregion

		#region Implementation (helpers)

			/// <exception cref="ArgumentOutOfRangeException">
			///		<para><paramref name="index"/> is less than zero</para>
			///		<para>-or-</para>
			///		<para><paramref name="index"/> is equal to or greater than <see cref="TextStyleCollection.Count"/>.</para>
			/// </exception>
			private void ValidateIndex(int i)
			{
				ValidateIndex(i, false);
			}

			/// <exception cref="ArgumentOutOfRangeException">
			///		<para><paramref name="index"/> is less than zero</para>
			///		<para>-or-</para>
			///		<para><paramref name="index"/> is equal to or greater than <see cref="TextStyleCollection.Count"/>.</para>
			/// </exception>
			private void ValidateIndex(int i, bool allowEqualEnd)
			{
				int max = (allowEqualEnd)?(m_count):(m_count-1);
				if (i < 0 || i > max)
					throw new System.ArgumentOutOfRangeException("Index was out of range.  Must be non-negative and less than the size of the collection.", (object)i, "Specified argument was out of the range of valid values.");
			}
		
			private bool NeedsGrowth(int newItems)
			{
				return ((m_count + newItems) > this.Capacity);
			}

			private bool NeedsGrowth()
			{
				return (m_count >= Capacity);
			}
		
			private void Grow(int newItems)
			{
				if (NeedsGrowth(newItems))
				{
					++m_version;
				
					TextStyle[] temp = new TextStyle[m_count + newItems];
					Array.Copy(m_array, temp, m_array.Length);
					m_array = temp;
				}
			}

			private void Grow()
			{			
				if (NeedsGrowth())
				{
					++m_version;

					TextStyle[] temp = new TextStyle[m_count * 2];
					Array.Copy(m_array, temp, m_array.Length);
					m_array = temp;
				}
			}

			private bool NeedsTrimming()
			{
				return (m_count <= Capacity / 3);
			}

			private void Trim()
			{
				if (NeedsTrimming())
				{
					++m_version;
				
					TextStyle[] temp = new TextStyle[m_count];
					Array.Copy(m_array, temp, m_array.Length);
					m_array = temp;
				}
			}

		#endregion
		
		#region Implementation (ICollection)

			void ICollection.CopyTo(Array array, int start)
			{
				this.CopyTo((TextStyle[])array, start);
			}

		#endregion

		#region Implementation (IList)

			object IList.this[int i]
			{
				get { return (object)this[i]; }
				set { this[i] = (TextStyle)value; }
			}

			int IList.Add(object x)
			{
				return this.Add((TextStyle)x);
			}

			bool IList.Contains(object x)
			{
				return this.Contains((TextStyle)x);
			}

			int IList.IndexOf(object x)
			{
				return this.IndexOf((TextStyle)x);
			}

			void IList.Insert(int pos, object x)
			{
				this.Insert(pos, (TextStyle)x);
			}

			void IList.Remove(object x)
			{
				this.Remove((TextStyle)x);
			}

			void IList.RemoveAt(int pos)
			{
				this.RemoveAt(pos);
			}

		#endregion

		#region Implementation (IEnumerable)

			IEnumerator IEnumerable.GetEnumerator()
			{
				return (IEnumerator)(this.GetEnumerator());
			}

		#endregion

		#region Nested enumerator class
			/// <summary>
			///		Supports simple iteration over a <see cref="TextStyleCollection"/>.
			/// </summary>
			private class Enumerator : IEnumerator, ITextStyleCollectionEnumerator
			{
			#region Implementation (data)
			
				private TextStyleCollection m_collection;
				private int m_index;
				private int m_version;
			
			#endregion
		
			#region Construction
			
				/// <summary>
				///		Initializes a new instance of the <c>Enumerator</c> class.
				/// </summary>
				/// <param name="tc"></param>
				internal Enumerator(TextStyleCollection tc)
				{
					m_collection = tc;
					m_index = -1;
					m_version = tc.m_version;
				}
			
			#endregion
	
			#region Operations (type-safe IEnumerator)
			
				/// <summary>
				///		Gets the current element in the collection.
				/// </summary>
				public TextStyle Current
				{
					get { return m_collection[m_index]; }
				}

				/// <summary>
				///		Advances the enumerator to the next element in the collection.
				/// </summary>
				/// <exception cref="InvalidOperationException">
				///		The collection was modified after the enumerator was created.
				/// </exception>
				/// <returns>
				///		<c>true</c> if the enumerator was successfully advanced to the next element; 
				///		<c>false</c> if the enumerator has passed the end of the collection.
				/// </returns>
				public bool MoveNext()
				{
					if (m_version != m_collection.m_version)
						throw new System.InvalidOperationException("Collection was modified; enumeration operation may not execute.");

					++m_index;
					return (m_index < m_collection.Count) ? true : false;
				}

				/// <summary>
				///		Sets the enumerator to its initial position, before the first element in the collection.
				/// </summary>
				public void Reset()
				{
					m_index = -1;
				}
			#endregion
	
			#region Implementation (IEnumerator)
			
				object IEnumerator.Current
				{
					get { return (object)(this.Current); }
				}
			
			#endregion
			}
        #endregion
        
        #region Nested Syncronized Wrapper class
			private class SyncTextStyleCollection : TextStyleCollection
			{
            #region Implementation (data)
				private TextStyleCollection m_collection;
				private object m_root;
            #endregion

            #region Construction
				internal SyncTextStyleCollection(TextStyleCollection list)
				{
					m_root = list.SyncRoot;
					m_collection = list;
				}
            #endregion
            
            #region Type-safe ICollection
				public override void CopyTo(TextStyle[] array)
				{
					lock(this.m_root)
						m_collection.CopyTo(array);
				}

				public override void CopyTo(TextStyle[] array, int start)
				{
					lock(this.m_root)
						m_collection.CopyTo(array,start);
				}
				public override int Count
				{
					get
					{ 
						lock(this.m_root)
							return m_collection.Count;
					}
				}

				public override bool IsSynchronized
				{
					get { return true; }
				}

				public override object SyncRoot
				{
					get { return this.m_root; }
				}
            #endregion
            
            #region Type-safe IList
				public override TextStyle this[int i]
				{
					get
					{
						lock(this.m_root)
							return m_collection[i];
					}
					set
					{
						lock(this.m_root)
							m_collection[i] = value; 
					}
				}

				public override int Add(TextStyle x)
				{
					lock(this.m_root)
						return m_collection.Add(x);
				}
            
				public override void Clear()
				{
					lock(this.m_root)
						m_collection.Clear();
				}

				public override bool Contains(TextStyle x)
				{
					lock(this.m_root)
						return m_collection.Contains(x);
				}

				public override int IndexOf(TextStyle x)
				{
					lock(this.m_root)
						return m_collection.IndexOf(x);
				}

				public override void Insert(int pos, TextStyle x)
				{
					lock(this.m_root)
						m_collection.Insert(pos,x);
				}

				public override void Remove(TextStyle x)
				{           
					lock(this.m_root)
						m_collection.Remove(x);
				}

				public override void RemoveAt(int pos)
				{
					lock(this.m_root)
						m_collection.RemoveAt(pos);
				}
            
				public override bool IsFixedSize
				{
					get {return m_collection.IsFixedSize;}
				}

				public override bool IsReadOnly
				{
					get {return m_collection.IsReadOnly;}
				}
            #endregion

            #region Type-safe IEnumerable
				public override ITextStyleCollectionEnumerator GetEnumerator()
				{
					lock(m_root)
						return m_collection.GetEnumerator();
				}
            #endregion

            #region Public Helpers
				// (just to mimic some nice features of ArrayList)
				public override int Capacity
				{
					get
					{
						lock(this.m_root)
							return m_collection.Capacity;
					}
                
					set
					{
						lock(this.m_root)
							m_collection.Capacity = value;
					}
				}

				public override int AddRange(TextStyleCollection x)
				{
					lock(this.m_root)
						return m_collection.AddRange(x);
				}

				public override int AddRange(TextStyle[] x)
				{
					lock(this.m_root)
						return m_collection.AddRange(x);
				}
            #endregion
			}
        #endregion

        #region Nested Read Only Wrapper class
			private class ReadOnlyTextStyleCollection : TextStyleCollection
			{
            #region Implementation (data)
				private TextStyleCollection m_collection;
            #endregion

            #region Construction
				internal ReadOnlyTextStyleCollection(TextStyleCollection list)
				{
					m_collection = list;
				}
            #endregion
            
            #region Type-safe ICollection
				public override void CopyTo(TextStyle[] array)
				{
					m_collection.CopyTo(array);
				}

				public override void CopyTo(TextStyle[] array, int start)
				{
					m_collection.CopyTo(array,start);
				}
				public override int Count
				{
					get {return m_collection.Count;}
				}

				public override bool IsSynchronized
				{
					get { return m_collection.IsSynchronized; }
				}

				public override object SyncRoot
				{
					get { return this.m_collection.SyncRoot; }
				}
            #endregion
            
            #region Type-safe IList
				public override TextStyle this[int i]
				{
					get { return m_collection[i]; }
					set { throw new NotSupportedException("This is a Read Only Collection and can not be modified"); }
				}

				public override int Add(TextStyle x)
				{
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}
            
				public override void Clear()
				{
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}

				public override bool Contains(TextStyle x)
				{
					return m_collection.Contains(x);
				}

				public override int IndexOf(TextStyle x)
				{
					return m_collection.IndexOf(x);
				}

				public override void Insert(int pos, TextStyle x)
				{
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}

				public override void Remove(TextStyle x)
				{           
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}

				public override void RemoveAt(int pos)
				{
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}
            
				public override bool IsFixedSize
				{
					get {return true;}
				}

				public override bool IsReadOnly
				{
					get {return true;}
				}
            #endregion

            #region Type-safe IEnumerable
				public override ITextStyleCollectionEnumerator GetEnumerator()
				{
					return m_collection.GetEnumerator();
				}
            #endregion

            #region Public Helpers
				// (just to mimic some nice features of ArrayList)
				public override int Capacity
				{
					get { return m_collection.Capacity; }
                
					set { throw new NotSupportedException("This is a Read Only Collection and can not be modified"); }
				}

				public override int AddRange(TextStyleCollection x)
				{
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}

				public override int AddRange(TextStyle[] x)
				{
					throw new NotSupportedException("This is a Read Only Collection and can not be modified");
				}
            #endregion
			}
        #endregion
		}
	}
}
