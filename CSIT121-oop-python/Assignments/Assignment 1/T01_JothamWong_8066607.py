# File Name: T01_JothamWong_8066607.txt

from datetime import datetime

class CustOrder:
    
    """class variable"""
    __num_of_orders = 0
    __todays_date = datetime.now() 
    __delivery_date_default = "To Be Confirmed"
    __date_input_format = '%d/%m/%Y %H:%M'
    __date_display_format = '%d-%b-%Y %I:%M%p'


    """Construct CustOrder"""
    def __init__(self, recipientName, recipientAddress, orderItem, deliveryDate = __delivery_date_default):
        self.__createRefNo()
        self.__name = recipientName
        self.__address = recipientAddress
        self.__orderDate = CustOrder.__todays_date    
        self.__createDeliveryDate(deliveryDate)      
        """Create list of items and add item inside"""
        self.__orderList = [orderItem]
        

    """Private methods"""
    def __createRefNo(self):
        CustOrder.__num_of_orders += 1
        self.__refNo = str(CustOrder.__num_of_orders).zfill(3)
    

    def __createDeliveryDate(self, dateString):
        temp = datetime.strptime(dateString, CustOrder.__date_input_format)
        if temp < self.__orderDate:
            self.__deliveryDate = CustOrder.__delivery_date_default
            return False
        else:
            self.__deliveryDate = temp
            return True
    

    """Accessor Methods"""
    def refNo(self):
        return self.__refNo

    def name(self):
        return self.__name

    def address(self):
        return self.__address
    
    def orderDate(self):
        return self.__orderDate.strftime(CustOrder.__date_display_format)
        
    def deliveryDate(self):
        # if isinstance(self.__deliveryDate, str):
        if type(self.__deliveryDate) == str:
            return self.__deliveryDate
        else:
            return self.__deliveryDate.strftime(CustOrder.__date_display_format)             

    def orderList(self):
        return self.__orderList

    """Setter methods"""
    def setAddress(self, newAddress):
        self.__address = str(newAddress)

    def setDeliveryDate(self, dateString):
        temp = datetime.strptime(dateString, CustOrder.__date_input_format)
        if temp < self.__orderDate:
            self.__deliveryDate = CustOrder.__delivery_date_default
            return False
        else:
            self.__deliveryDate = temp
            return True


    """Add/Remove Items"""
    def addItem(self, newItem):
        unique = True
        i = 0
        while unique and i<len(self.__orderList):
            if self.__orderList[i].prod() == newItem.prod():
                newQty = self.__orderList[i].qty() + newItem.qty()     
                self.__orderList[i].setQty(newQty) 
                return False
            else:
                i += 1
        if unique:
            self.__orderList.append(newItem)


    def removeItem(self, itemToRemove):
        removed = False
        for item in self.__orderList:
            if item.prod() == itemToRemove.prod(): 
                self.__orderList.remove(itemToRemove)    
                return True
        return removed 
                

    """Calculation Method"""
    def getTotal(self):
        sum = 0
        for item in self.__orderList:
            sum += item.getActualAmount()    
        return round(sum, 2)

    """def getTotalDiscount(self):
        discount = 0
        for item in self.__orderList:
            discount += item.getDiscountAmt()"""


    """Display method"""
    def displayOrderList(self):
        orderDetails = ""
        for i in range(len(self.__orderList)):
            orderDetails += f"{str(i+1)}{'.':<5}{self.__orderList[i].prod():<25}"
            if self.__orderList[i].getDiscountAmt():
                orderDetails += f"{self.__orderList[i].unitPrice():.2f}{'*':<11}"
            else:
                orderDetails += f"{self.__orderList[i].unitPrice():<15.2f}"
            orderDetails += f"{self.__orderList[i].qty():<15}${self.__orderList[i].getActualAmount():.2f}\n"
        return orderDetails

    def __str__(self):
        display = "=" * 25 + "\n"
        display += f"Order ref: {self.__refNo}\n"
        display += f"Name: {self.__name}\n"
        display += f"Address: {self.__address}\n"
        display += f"Date ordered/delivered: {self.orderDate()} / {self.deliveryDate()}\n\n"
        display += f"{'S/N':<6}{'Product':<25}{'Price':<15}{'Qty':<15}{'SubTotal'}\n"
        display += f"{self.displayOrderList()}\n"
        display += f"{' ' * 46}{'Total':<15}${self.getTotal():.2f}\n"
        display += f"* - discounted price\n{'=' * 29}"

        return display
        
        


class OrderItem:

    "Class variable"
    __minimum_qty = 1
    __no_discount = 0


    """Create OrderItem"""
    def __init__(self, prod, unitPrice, qty=__minimum_qty, discount=__no_discount):
        self.__prod = prod
        self.setUnitPrice(unitPrice)
        self.setQty(qty)
        self.setDiscount(discount)


    """getter methods"""
    def prod(self):
        return str(self.__prod)
    
    def unitPrice(self):
        return self.__unitPrice

    def qty(self):
        return self.__qty

    """Setter methods"""
    def setUnitPrice(self, Amt):
        if Amt < 0:
            print("Price Error - Unit price cannot be less than zero")
        else:
            self.__unitPrice = round(Amt,2)

    def setDiscount(self, discount):
        if discount < 0:
            print("Discount Error - Discount cannot be less than zero")
        else:
            self.__discount = int(discount)
        
    def setQty(self, newQty):
        if newQty < 1:
            print("Quantity Error - Quantity cannot be less than one")
        elif newQty != int(newQty):
            print("Quantity Error - Quantity cannot be a floating point")
        else:
            self.__qty = newQty


    """Calculation Methods"""
    def getTotalAmount(self):
        return self.__unitPrice * self.__qty
    
    def getDiscountAmt(self):
        return self.__unitPrice * self.__qty * self.__discount/100

    def getActualAmount(self):
        return self.getTotalAmount() - self.getDiscountAmt()
        
    

    """display methods"""
    def __str__(self):
        return f"Product: {self.__prod}\nQty: {self.__qty}\nAmount Due: ${self.getActualAmount():.2f}"



if __name__ == "__main__":
    """Create objects"""
    item1 = OrderItem("Mars", 2.50)
    item2 = OrderItem("Maggie Mee", 3.50, 5, 15)
    item3 = OrderItem("Milo", 2, 6, 20)
    item4 = OrderItem("Maggie Mee", 3.50)
    cart1 = CustOrder("Jotham", "Blk 220 Jurong West 478220", item1, "10/10/2024 19:00")

    print(item1)
    print(cart1)
    #print(cart1.orderList())
    print()

    """Set Delivery Date"""
    print("After setting valid delivery date")
    cart1.setDeliveryDate("30/10/2024 12:00")
    print(cart1)
    print()


    """Add items into cart"""
    print("\nAfter adding item2 and item3")
    cart1.addItem(item2)
    cart1.addItem(item3)
    print(cart1)
    print()
    
    """Add duplicate to cart"""
    print("\nAfter adding Duplicate item")
    cart1.addItem(item4)
    print(cart1)
    print()

    """Remove items from cart"""
    print("\nAfter removing items")
    cart1.removeItem(item2)
    print(cart1)
    print()

    """Remove nonexistent item"""
    print("\nAfter removing nonexistent items")
    cart1.removeItem(item2)
    print(cart1)


    