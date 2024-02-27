using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SEMINAR1_1062
{
    internal class Student
    {
        public int varsta;
        private string nume;
        protected float medie;

        //constructor default
        public Student ()
        {
            this.varsta = 0;
            this.nume = "Anonim";
            this.medie = 0.0f;
        }
        //constructor cu parametrii
        public Student(int v, string n, float m)
        {
            varsta = v;
            nume = n;
            medie = m;
        }

        //constructor de copiere
        public Student(Student s)
        {
            this.varsta = s.varsta;
            this.nume = s.nume;
            this.medie = s.medie;
        }

        public void afisare ()
        {
            Console.WriteLine("Studentul {0} cu varsta {1} are media {2}", nume, varsta, medie);
        }

        //hover pe numele clasei si dupa Generate Overrides
        public override string ToString()
        {
            return "Studentul " + nume + " cu varsta " + varsta + " are media " + medie;
        }


        //value cuvant cheie care tine locul parametrul functiei din C
        public string Nume
        {
            get { return nume; }
            set { if (value!= null) nume = value; }
        }
    }
}
