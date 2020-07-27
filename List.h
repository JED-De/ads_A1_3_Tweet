#ifndef _LIST_H
#define _LIST_H
#include "Node.h"
#include <string>
#include <iostream>

template <typename T> class List
{
	/*
	Die Klasse List dient zur Verwaltung von Knoten (Node). Mit Hilfe der Klasse List
	kann ein Stapel oder Warteschlange realisiert werden.
	*/
private:
	struct form { std::string start = "<< "; std::string zwischen = ", "; std::string ende = " >>\n"; } list_form;
	Node<T>* head_tail;						// Zeiger auf Kopf- und End-Element -> next der 1. Knoten; -> prev der letzte Knoten
	int list_size;							// L�nge der Kette
	bool temp;								// normalerweise false; ist true, wenn es sich um eine temor�re Liste handelt
											// die innerhalb der �berladenen Operatoren angelegt wird
public:
	template <typename T>
	friend Node<T>* get_anker(List<T>& l);
	template <typename T>
	friend int get_AnzahlNodes(List<T>& l);
	template <typename T>
	friend std::ostream& operator << (std::ostream& stream, const List<T>& Liste);
	List()
	{
		// Konstruktor f�r eine leere Liste
		head_tail = new Node<T>;
		list_size = 0;
		temp = false;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
	}

	List(const List<T>& _List)
	{
		// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
		// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
		list_form = _List.list_form;
		head_tail = new Node<T>;
		list_size = 0;
		temp = _List.temp;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
		Node<T>* tmp_node;
		tmp_node = _List.head_tail->next;
		while (tmp_node != _List.head_tail)
		{
			head_tail->prev = new Node(tmp_node->key, head_tail->prev->next, head_tail->prev);
			head_tail->prev->prev->next = head_tail->prev;
			list_size++;
			tmp_node = tmp_node->next;
		}
		if (_List.temp) delete& _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	}

	List(const List<T>* _List)
	{
		// Konstruktor mit �bergabe einer Liste, die dann kopiert wird.
		// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
		list_form = _List->list_form;
		head_tail = new Node<T>;
		list_size = 0;
		temp = _List->temp;
		head_tail->next = head_tail;
		head_tail->prev = head_tail;
		Node<T>* tmp_node;
		tmp_node = _List->head_tail->next;
		while (tmp_node != _List->head_tail)
		{
			head_tail->prev = new Node<T>(tmp_node->key, head_tail->prev->next, head_tail->prev);
			head_tail->prev->prev->next = head_tail->prev;
			list_size++;
			tmp_node = tmp_node->next;
		}
		if (_List->temp) delete _List;		// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
	}

	~List()
	{
		// Dekonstruktor
		// Alle Knoten der Liste m�ssen gel�scht werden, wenn die Liste gel�scht wird.
	/*
		hier alle Knoten l�schen, die im Objekt List allokiert wurden
	*/
		if (this->head_tail != nullptr)
		{
			Node<T>* ptr = this->head_tail->next;
			while (ptr->next != this->head_tail)
			{
				ptr = ptr->next;
				delete this->head_tail->next;
				this->head_tail->next = ptr;
			}
			delete this->head_tail;
			this->head_tail = nullptr;
			this->list_size = 0;
		}

	}

	void insertFront(T key)
	{
		// Einf�gen eines neuen Knotens am Anfang der Liste
	/*
		Einen neuen Knoten mit dem Schl�sselwert key am Anfang der Liste einf�gen
	*/

		Node<T> * x = new Node<T>;
		x->key = key;
		x->next = head_tail->next;
		x->prev = head_tail;
		head_tail->next->prev = x;
		head_tail->next = x;
		list_size++;
	}

	void insertFront(List<T>& _List)
	{
		// Einf�gen einer vorhandenen Liste am Anfang
		/*
		Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
		Die einzuf�gende Liste _List ist anschlie�end leer.
		Es darf keine Schleife und kein new benutzt werden.
		*/
		/*
			Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
			Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
		*/

		_List.head_tail->next->prev = this->head_tail;
		_List.head_tail->prev->next = this->head_tail->next;
		this->head_tail->next->prev = _List.head_tail->prev;
		this->head_tail->next = _List.head_tail->next;

		this->list_size += _List.list_size;
		_List.head_tail->next = _List.head_tail;
		_List.head_tail->prev = _List.head_tail;

	}

	void insertFront(List<T>* _List)
	{
		// Einf�gen einer vorhandenen Liste am Anfang
		/*
		Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
		Die einzuf�gende Liste _List ist anschlie�end leer.
		Es darf keine Schleife und kein new benutzt werden.
		*/
		/*
			Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
			Diese Knoten (koplette Kette) werden an den Anfang der Liste (this) �bertragen ohne sie zu kopieren!
		*/
		_List->head_tail->next->prev = this->head_tail;
		_List->head_tail->prev->next = this->head_tail->next;
		this->head_tail->next->prev = _List->head_tail->prev;
		this->head_tail->next = _List->head_tail->next;

		this->list_size += _List->list_size;
		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}

	void insertBack(T key)
	{
		// Einf�gen eines neuen Knotens am Ende der Liste
	/*
		Einen neuen Knoten mit dem Schl�sselwert key am Ende der Liste einf�gen
	*/
		Node<T> * x = new Node<T>();
		x->key = key;
		x->next = head_tail;
		x->prev = head_tail->prev;
		head_tail->prev->next = x;
		head_tail->prev = x;
		list_size++;
	}

	void insertBack(List<T>& _List)
	{
		// Einf�gen einer vorhandenen Liste am Ende
		/*
		Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
		Die einzuf�gende Liste _List ist anschlie�end leer.
		Es darf keine Schleife und kein new benutzt werden.
		*/
		/*
			Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
			Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
		*/
		_List.head_tail->prev->next = this->head_tail;
		_List.head_tail->next->prev = this->head_tail->prev;
		this->head_tail->prev->next = _List.head_tail->next;
		this->head_tail->prev = _List.head_tail->prev;

		this->list_size += _List.list_size;
		_List.head_tail->next = _List.head_tail;
		_List.head_tail->prev = _List.head_tail;
	}

	void insertBack(List<T>* _List)
	{
		// Einf�gen einer vorhandenen Liste am Ende
		/*
		Die einzuf�genden Knoten werden �bernommen (nicht kopiert)
		Die einzuf�gende Liste _List ist anschlie�end leer.
		Es darf keine Schleife und kein new benutzt werden.
		*/
		/*
			Es wird ein Objekt �bergeben in dem Knoten vorhanden sein k�nnen.
			Diese Knoten (koplette Kette) werden an das Ende der Liste (this) angehangen ohne sie zu kopieren!
		*/
		_List->head_tail->prev->next = this->head_tail;
		_List->head_tail->next->prev = this->head_tail->prev;
		this->head_tail->prev->next = _List->head_tail->next;
		this->head_tail->prev = _List->head_tail->prev;

		this->list_size += _List->list_size;
		_List->head_tail->next = _List->head_tail;
		_List->head_tail->prev = _List->head_tail;
	}

	bool getFront(T& key)
	{
		// entnehmen des Knotens am Anfang der Liste
		// der Wert wird als Parameter zur�ckgegeben
		// der Knoten wird entnommen
	/*
		Der Wert des vorderen Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
		Die Methode del(key) darf nicht zum l�schen benutzt werden.
	*/
		if (this->list_size != 0)
		{
			Node<T>* tmp = this->head_tail->next;
			key = tmp->key;
			tmp->next->prev = this->head_tail;
			this->head_tail->next = tmp->next;
			delete tmp;
			this->list_size--;
			return true;

		}
		return false;
	}

	bool getBack(T& key)
	{	// entnehmen des Knotens am Ende der Liste
		// der Wert wird als Parameter zur�ckgegeben
		// der Knoten wird entnommen
	/*
		Der Wert des letzten Schl�sselknotens wird r�ckgegeben und der Knoten gel�scht.
		Die Methode del(key) darf nicht zum l�schen benutzt werden.
	*/
		if (this->list_size != 0)
		{
			Node<T>* tmp = this->head_tail->prev;
			key = tmp->key;
			this->head_tail->prev = tmp->prev;
			tmp->prev->next = this->head_tail;

			delete tmp;
			this->list_size--;
			return true;
		}
		return false;
	}

	bool del(T key)
	{
		// L�schen eines gegebenen Knotens
	/*
		L�schen des Knotens mit dem Schl�ssel key
	*/
		if (this->search(key))
		{
			Node<T>* tmp = this->head_tail;
			while (tmp->next != this->head_tail)
			{
				tmp = tmp->next;
				if (tmp->key == key)
				{
					tmp->prev->next = tmp->next;
					tmp->next->prev = tmp->prev;
					delete tmp;
					this->list_size--;
					return true;
				}
			}
		}
		return false;
	}

	bool search(T key)
	{
		// suchen eines Knotens
	/*
		suchen ob ein Knoten mit dem Schl�ssel key existiert.
	*/
		if (this->list_size != 0)
		{
			Node<T>* tmp = this->head_tail;
			while (tmp->next != this->head_tail)
			{
				tmp = tmp->next;
				if (tmp->key == key)
					return true;
			}
		}
		return false;
	}

	bool swap(T key1, T key2)
	{
		// Vertauschen von zwei Knoten
		// Dabei werden die Zeiger der Knoten und deren Nachbarn ver�ndert.
	/*
		Vertauschen von zwei Knoten mit dem key1 und dem key2
		Es d�rfen nicht nur einfach die Schl�ssel in den Knoten getauscht werden!
		Die Knoten sind in der Kette umzuh�ngen.
	*/
		if (this->search(key1) && this->search(key2))
		{
			Node<T>* tmp1 = this->head_tail, *tmp2 = this->head_tail;
			while (tmp1->next != this->head_tail)
			{
				tmp1 = tmp1->next;
				if (tmp1->key == key1)
					break;
			}
			while (tmp2->next != this->head_tail)
			{
				tmp2 = tmp2->next;
				if (tmp2->key == key2)
					break;
			}
			Node<T>* tmp = tmp2->prev->next;
			tmp2->prev->next = tmp1->prev->next;
			tmp1->prev->next = tmp;
			tmp = tmp2->prev;
			tmp2->prev = tmp1->prev;
			tmp1->prev = tmp;
			tmp = tmp2->next->prev;
			tmp2->next->prev = tmp1->next->prev;
			tmp1->next->prev = tmp;
			tmp = tmp2->next;
			tmp2->next = tmp1->next;
			tmp1->next = tmp;
			return true;
		}
		return false;
	}

	int size(void)
	{
		// R�ckgabe der Knoten in der Liste mit O(1)
	/*
		Anzahl der Knoten in der Liste zur�ckgeben.
	*/
		return this->list_size;
	}

	bool test(void)
	{
		// Testmethode: die Methode durchl�uft die Liste vom Anfang bis zum Ende und zur�ck
		// Es werden dabei die Anzahl der Knoten gez�hlt.
		// Stimmt die Anzahl der Knoten �berein liefert die Methode true
		Node<T>* tmp = head_tail->next;
		int i_next = 0, i_prev = 0;
		while (tmp != head_tail) {
			tmp = tmp->next;
			if (i_next > list_size) return false;
			i_next++;
		}
		if (i_next != list_size) return false;
		tmp = head_tail->prev;
		while (tmp != head_tail) {
			tmp = tmp->prev;
			if (i_prev > list_size) return false;
			i_prev++;
		}
		return i_prev == i_next;
	}

	List& operator = (const List<T>& _List)
	{
		// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
		// Kopiert wird in das Objekt "this"
		if (this == &_List) return *this;		//  !! keine Aktion notwendig
		list_form = _List.list_form;
		Node<T>* tmp_node;
		if (list_size)
		{
			Node<T>* tmp_del;
			tmp_node = head_tail->next;
			while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
			{
				tmp_del = tmp_node;
				tmp_node = tmp_node->next;
				delete tmp_del;
			}
			list_size = 0;
			head_tail->next = head_tail;
			head_tail->prev = head_tail;
		}
		tmp_node = _List.head_tail->next;		// Die Listen-Knotenwerte werden kopiert
		while (tmp_node != _List.head_tail)
		{
			insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
		if (_List.temp) delete& _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
		return *this;
	}

	List& operator = (const List<T>* _List)
	{
		// in dem Objekt _List sind die Knotenwerte enthalten, die Kopiert werden sollen.
		// Kopiert wird in das Objekt "this"
		if (this == _List) return *this;		//  !! keine Aktion notwendig
		list_form = _List->list_form;
		Node<T>* tmp_node;
		if (list_size)
		{
			Node<T>* tmp_del;
			tmp_node = head_tail->next;
			while (tmp_node != head_tail)		// Alle eventuell vorhandenen Knoten in this l�schen
			{
				tmp_del = tmp_node;
				tmp_node = tmp_node->next;
				delete tmp_del;
			}
			list_size = 0;
			head_tail->next = head_tail;
			head_tail->prev = head_tail;
		}
		tmp_node = _List->head_tail->next;
		while (tmp_node != _List->head_tail)	// Die Listen-Knotenwerte werden kopiert
		{
			insertBack(tmp_node->key);
			tmp_node = tmp_node->next;
		}
		if (_List->temp) delete _List;			// ist die �bergebene Liste eine tempor�re Liste? -> aus Operator +
		return *this;
	}

	List& operator + (const List<T>& List_Append)
	{
		// Die Methode +
		// Es werden zwei Listen aneinander gehangen.
		// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
		Node<T>* tmp_node;
		List<T>* tmp;
		if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
			tmp = this;
		}
		else {
			tmp = new List<T>(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
			tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
		}
		if (List_Append.list_size) {					// anh�ngen der �bergebenen Liste an tmp
			tmp_node = List_Append.head_tail->next;
			while (tmp_node != List_Append.head_tail) {
				tmp->insertBack(tmp_node->key);
				tmp_node = tmp_node->next;
			}
		}
		if (List_Append.temp) delete& List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht						
		return *tmp;
	}

	List& operator + (const List<T>* List_Append)
	{
		// Die Methode +
		// Es werden zwei Listen aneinander gehangen.
		// Dabei werden beide Ursprungslisten nicht ver�ndert. Es entsteht eine neue Ergebnisliste.
		Node<T>* tmp_node;
		List<T>* tmp;
		if (temp) {										// this ist eine tempor�re Liste und kann ver�ndert werden
			tmp = this;
		}
		else {
			tmp = new List<T>(this);						// this ist keine tempor�re Liste -> Kopie erzeugen
			tmp->temp = true;							// Merker setzten, dass es sich um eine tempor�re Liste handelt
		}
		if (List_Append->list_size) {					// anh�ngen der �bergebenen Liste an tmp
			tmp_node = List_Append->head_tail->next;
			while (tmp_node != List_Append->head_tail) {
				tmp->insertBack(tmp_node->key);
				tmp_node = tmp_node->next;
			}
		}
		if (List_Append->temp) delete List_Append;		// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht					
		return *tmp;
	}

	void format(const std::string & start, const std::string & zwischen, const std::string & ende)
	{
		// Setzen des Formates f�r die Ausgabesteuerung der Liste bei cout
		// das Format wird f�r den �berladenen Operator << verwendet
		list_form.start = start;
		list_form.zwischen = zwischen;
		list_form.ende = ende;
	}

	template <typename T>
	friend std::ostream& operator<<(std::ostream & stream, List<T> const& Liste)
	{
		// Ausgabe der Liste mit cout
		stream << Liste.list_form.start;
		for (Node<T>* tmp = Liste.head_tail->next; tmp != Liste.head_tail; tmp = tmp->next)
			stream << tmp->key << (tmp->next == Liste.head_tail ? Liste.list_form.ende : Liste.list_form.zwischen);
		if (Liste.temp) delete & Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
		return stream;
	}

	template <typename T>
	friend std::ostream & operator << (std::ostream & stream, List<T> const* Liste)
	{
		// Ausgabe der Liste mit cout
		stream << Liste->list_form.start;
		for (Node<T>* tmp = Liste->head_tail->next; tmp != Liste->head_tail; tmp = tmp->next)
			stream << tmp->key << (tmp->next == Liste->head_tail ? Liste->list_form.ende : Liste->list_form.zwischen);
		if (Liste->temp) delete Liste;			// wurde eine tempor�re Liste �bergeben, dann wird diese gel�scht
		return stream;
	}
};

#endif

