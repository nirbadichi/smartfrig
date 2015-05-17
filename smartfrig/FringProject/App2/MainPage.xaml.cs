using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=391641

namespace App2
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        private Popup popup;

        public ObservableCollection<Item> ItemsCollection = new ObservableCollection<Item>();

        public MainPage()
        {
            this.InitializeComponent();
            System.Threading.Tasks.Task.Delay(2000).Wait();


            this.NavigationCacheMode = NavigationCacheMode.Required;
            ItemsCollection.Add(new Item("Danone",
      1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));
            ItemsCollection.Add(new Item("Bamba",
     1313123, new DateTime(2015, 3, 6), "images/bamba.jpg"));
            ItemsCollection.Add(new Item("Bamba",
    1313123, new DateTime(2015, 3, 6), "images/bamba.jpg"));
            ItemsCollection.Add(new Item("Bamba",
    1313123, new DateTime(2015, 3, 6), "images/bamba.jpg"));
            ItemsCollection.Add(new Item("Bamba",
    1313123, new DateTime(2015, 3, 6), "images/bamba.jpg"));
            ItemsCollection.Add(new Item("Danone",
     1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));
            ItemsCollection.Add(new Item("Danone",
     1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));
            ItemsCollection.Add(new Item("Danone",
     1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));
            ItemsCollection.Add(new Item("Danone",
     1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));
            ItemsCollection.Add(new Item("Danone",
     1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));



            listOfItems.DataContext = ItemsCollection;
        }

        /// <summary>
        /// Invoked when this page is about to be displayed in a Frame.
        /// </summary>
        /// <param name="e">Event data that describes how this page was reached.
        /// This parameter is typically used to configure the page.</param>
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            // TODO: Prepare page for display here.

            // TODO: If your application contains multiple pages, ensure that you are
            // handling the hardware Back button by registering for the
            // Windows.Phone.UI.Input.HardwareButtons.BackPressed event.
            // If you are using the NavigationHelper provided by some templates,
            // this event is handled for you.
        }

        public class Item
        {
            public Item() { }
            public Item(string itemName, int itemId, DateTime itemExpiredDate, string imageUri)
            {
                Name = itemName;
                Id = itemId;
                ExpiredDate = itemExpiredDate;
                ImageUri = imageUri;
            }
            public string Name { get; set; }
            public int Id { get; set; }
            public string ImageUri { get; set; }
            public DateTime ExpiredDate { get; set; }

            // Override the ToString method.
            public override string ToString()
            {
                return " Name: " + Name + " Barcode: " + Id + ", ExpiredDate: " + ExpiredDate.ToString();
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            ItemsCollection.Add(new Item("Roi",
    1092312, new DateTime(2007, 2, 6), "images/danona.jpg"));
        }
    }
}
