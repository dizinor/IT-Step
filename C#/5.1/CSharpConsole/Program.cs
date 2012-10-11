using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CSharpConsole
{
    struct Article
    {
        public int idItem;
        public string nameItem;
        public int priceItem;
    }
    struct Client
    {
        public int idClient;
        public string name;
        public string adress;
        public int number;
        public int ammountRequest;
        public int totalCost;
    }
    struct RequestItem
    {
        public Article article;
        public int ammount;
    }
    struct Request
    {
        public int idRequest;
        public Client client;
        public DateTime date;
        public List<RequestItem> shopList;
        public int TotalCost
        {
            set
            {
                TotalCost = 0;
                foreach (RequestItem item in shopList)
                {
                    TotalCost += item.ammount * item.article.priceItem;
                }
            }
            get
            {
                return TotalCost;
            }
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
        }
    }
}

