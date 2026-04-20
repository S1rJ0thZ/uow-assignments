# Assignment 3 
#
# File name: T01_Jotham_8066607.py

import csv
import re
from datetime import datetime
#import logging

# Configure logging to capture errors
#logging.basicConfig(filename='error_log.txt', level=logging.ERROR, format='%(asctime)s - %(message)s')


class ResaleTransaction:
    """
    Create one resale transaction
    """
    def __init__(self, month:str, town:str, flatType:str, block: str, streetName: str,\
        storeyRange: str, floorAreaSqm: int, flatModel: str, leaseCommenceDate:datetime,\
            remainingLease: str, resalePrice: int):
        self.saleMonth = month
        self.__town = town  #No validation required
        self.flatType = flatType
        self.block = block
        self.streetName = streetName
        self.__storey_range = storeyRange
        self.floorAreaSqm = floorAreaSqm      
        self.__flat_model = flatModel   #No validation required
        self.leaseCommenceDate = leaseCommenceDate
        self.remainingLease = remainingLease     # calculate using datetime, determine if values are accurate
        self.resalePrice = resalePrice 
        

    # get methods
    @property
    def saleMonth(self):
        return self.__saleMonth

    @property
    def town(self):
        return self.__town
    
    # Use Regular Expression to do setter ########
    @property
    def flatType(self):
        return self.__flat_type
    
    @property
    def block(self):
        return self.__block

    @property
    def streetName(self):
        return self.__street_name

    @property
    def storeyRange(self):
        return self.__storey_range
    ###############################################

    @property
    def floorAreaSqm(self):
        return self.__floor_area_sqm

    @property
    def flatModel(self):
        return self.__flat_model
    
    @property
    def leaseCommenceDate(self):
        return self.__lease_commence_date

    @property
    def remainingLease(self):
        return self.__remaining_lease

    @property
    def resalePrice(self):
        return self.__resale_price


    # set methods
    @saleMonth.setter
    def saleMonth(self, dateString):
        try:
            date = datetime.strptime(dateString, "%Y-%m")
            if (datetime.now().year, datetime.now().month) >= (date.year, date.month):
                self.__saleMonth = date
            else:
                raise ValueError("Sale date cannot be later than the current Year-Month")
        except ValueError as e:
            raise ValueError(f"{e}:{dateString}")
        
    @flatType.setter
    def flatType(self, flat):
        pattern1 = r"[1-5] ROOM"
        pattern2 = r"EXECUTIVE"
        match1 = re.match(pattern1, flat)
        match2 = re.match(pattern2, flat)
        try:
            if match1 or match2:
                self.__flat_type = flat
                    
            else:
                raise ValueError("Invalid Flat Type")
        except ValueError as e:
            raise ValueError(f"{e}:{flat}")

    @block.setter
    def block(self, block):
        pattern = r"[1-9]\d{0,2}[A-Z]?"
        match = re.match(pattern, block)
        try:
            if match:
                self.__block = block
            else:
                raise ValueError("Block is invalid")
        except ValueError as e:
            raise ValueError(f"{e}:{block}")

    @streetName.setter
    def streetName(self, streetName):
        pattern = r"[A-Z ]+[1-9]?\d?"
        match = re.match(pattern, streetName)
        try:
            if match:
                self.__street_name = streetName
            else:
                raise ValueError("Invalid Street Name")
        except ValueError as e:
            raise ValueError(f"{e}:{streetName}")

    # Use regex to retrieve the data
    @storeyRange.setter
    def storeyRange(self, storeyRange):
        pattern = r"\d{2} TO \d{2}"
        match = re.match(pattern, storeyRange)
        try:
            if match:
                self.__storey_range = storeyRange
            else:
                raise ValueError("Invalid Storey Range")
        except ValueError as e:
            raise ValueError(f"{e}:{storeyRange}")

    @floorAreaSqm.setter
    def floorAreaSqm(self, area):
        try:
            try:
                area = int(area)
            except:
                raise ValueError("Area must be an integer")
            if area > 0:
                self.__floor_area_sqm = area
            else:
                raise ValueError("Floor area must be positive")
        except ValueError as e:
            raise ValueError(f"{e}:{area}")

    @leaseCommenceDate.setter
    def leaseCommenceDate(self, dateString):
        try: 
            date = datetime.strptime(dateString, "%Y")
            if date.year > datetime.now().year:
                raise ValueError("Lease commencement cannot be later than today")
            else:
                self.__lease_commence_date = date
        except ValueError as e:
            raise ValueError(f"{e}:{dateString}")

    @remainingLease.setter
    def remainingLease(self, leaseDuration):
        pattern = r"[\d]+ years [\d]+ months"
        try:
            if re.match(pattern, leaseDuration):
                self.__remaining_lease = leaseDuration
            else:
                raise ValueError("Invalid lease duration")
        except ValueError as e:
            raise ValueError(f"{e}:{leaseDuration}")

    @resalePrice.setter
    def resalePrice(self, price):
        try:
            try:
                price = int(price)
            except:
                raise ValueError("Price must be an integer")
            if price > 0:
                self.__resale_price = price
            else:
                raise ValueError("Price must be a positive integer")
        except ValueError as e:
            raise ValueError(f"{e}:{price}")


    # Calculated values
    @property
    def pricePSF(self):
        sqf = self.__floor_area_sqm * 10.76391041671
        return round(self.__resale_price/sqf, 2)
    


class HDB_Resale_Admin():
    """
    Construct HDB Resale Administrator 
    """
    def __init__(self):
        self.__resales = []

    
    # Load method 
    def load(self):
        resaleFile = "Resale2024.csv"
        error_log = []
        line_number = 0

        try:
            with open(resaleFile, "r") as resaleData:
                # Return Iteratable of dictionaries
                reader =  csv.DictReader(resaleData)
                for row in reader:
                    line_number += 1
                    try:
                        transaction = ResaleTransaction(*row)
                        #resale = ResaleTransation(row["month"], row["town"], row["flat_type"], row["block"],\
                        #row["street_name"], row["storey_range"], row["floor_area_sqm"], row["flat_model"], row["lease_commence_date"], row["remaining_lease"],\
                        #row["resale_price"])
                        self.__resales.append(transaction)
                    except ValueError as e:
                        error_log.append(f"File line {line_number}: {e}")
                    except TypeError as e:
                        error_log.append(f"File line {line_number}: {e}")              
        except FileNotFoundError:
            print(f"File not found: {resaleFile}")


    # getter methods
    def get_town(self):
        townList = []
        for resale in self.__resales:
            townList.append(resale.town)
        return townList

    def get_flat_type(self):
        flatTypeList = []
        for resale in self.__resales:
            flatTypeList.append(resale.flatType)
        return flatTypeList

    def get_flat_model(self):
        flatModelList = []
        for resale in self.__resales:
            flatModelList.append(resale.flatModel)
        return flatModelList

    
    # search method
    def search(self, *, town= None, flat_type= None, flat_model= None, price_psf= None):
        if town and not isinstance(town, (list, tuple)):
            town = [town]
        if flat_type and not isinstance(flat_type, (list, tuple)):
            flat_type = [flat_type]
        if flat_model and not isinstance(flat_model, (list, tuple)):
            flat_model = [flat_model]
        if price_psf:
                price_psf = float(price_psf)

        results = []
        for resale in self.__resales:
            if town and resale.town not in town:
                continue
            if flat_type and resale.flatType not in flat_type:
                continue
            if flat_model and resale.flatModel not in flat_model:
                continue
            if price_psf and (resale.pricePSF < price_psf):
                continue
            results.append(resale)
        return results
    
        """
        results = self.resales
        if town:
            results = [resale for resale in results if resale.town in town]
        if flat_type:
            results = [resale for resale in results if resale.flat_type in flat_type]
        if flat_model:
            results = [resale for resale in results if resale.flat_model in flat_model]
        if price_psf:
            results = [resale for resale in results if resale.price_psf >= price_psf]
        return results

        """



def check_towns(towns):
	towns_data = ['TOA PAYOH', 'CHOA CHU KANG', 'BUKIT TIMAH', 'YISHUN', 'QUEENSTOWN', 'HOUGANG', 'JURONG WEST', 'WOODLANDS', 'CLEMENTI', 'PUNGGOL', 'BEDOK', 'PASIR RIS', 'BUKIT MERAH', 'SERANGOON', 'MARINE PARADE', 'ANG MO KIO', 'BUKIT PANJANG', 'BUKIT BATOK', 'KALLANG/WHAMPOA', 'BISHAN', 'CENTRAL AREA', 'SEMBAWANG', 'GEYLANG', 'TAMPINES', 'SENGKANG', 'JURONG EAST']
	towns_data = set(towns_data)
	towns = set(towns)
	return towns == towns_data


def check_flat_types(flat_types):
	flat_types_data = ['2 ROOM', '1 ROOM', '4 ROOM', '3 ROOM', '5 ROOM', 'EXECUTIVE', 'MULTI-GENERATION']
	flat_types_data = set(flat_types_data)
	flat_types = set(flat_types)
	return flat_types == flat_types_data


def check_flat_models(flat_models):
	flat_models_data = ['TYPE S2', 'MODEL A2', '3GEN', 'IMPROVED', 'STANDARD', 'APARTMENT', '2-ROOM', 'MAISONETTE', 'MODEL A-MAISONETTE', 'TYPE S1', 'TERRACE', 'MULTI GENERATION', 'NEW GENERATION', 'PREMIUM APARTMENT LOFT', 'MODEL A', 'SIMPLIFIED', 'DBSS', 'PREMIUM APARTMENT', 'ADJOINED FLAT']
	flat_models_data = set(flat_models)
	flat_models = set(flat_models)
	return flat_models == flat_models_data


def main():
	counter = 0
	app = HDB_Resale_Admin()
	app.load()
     
	print("Test get_town():")
	if(check_towns(app.get_town())):
		counter += 1

    print(f"Test cases passed:{counter}")

    
	print("Test get_flat_type():")
	if(check_flat_types(app.get_flat_type())):
		counter += 1
          
	print("Test get_flat_model():")
	if(check_flat_models(app.get_flat_model())):
		counter += 1
          
	print("Test search with different combinations - single value each:")
	print("Town - QUEENSTOWN")
	r = app.search(town=["QUEENSTOWN"])
	if(len(r) == 220):
		counter += 1

	print("Town - QUEENSTOWN flat_type=4 ROOM")
	r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"])
	if(len(r) == 83):
		counter += 1

	print("Town - QUEENSTOWN flat_model=MODEL A")
	r = app.search(town=["QUEENSTOWN"], flat_model=["MODEL A"])
	if(len(r) == 87):
		counter += 1

	print("Town - QUEENSTOWN price_psf=500")
	r = app.search(town=["QUEENSTOWN"], price_psf=500)
	if(len(r) == 202):
		counter += 1

	print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A")
	r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL A"])
	if(len(r) == 61):
		counter += 1

	print("Town - QUEENSTOWN  flat_type=4 ROOM price_psf=500")
	r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], price_psf=500)
	if(len(r) == 82):
		counter += 1

	print("Town - QUEENSTOWN flat_model=MODEL A price_psf=500")
	r = app.search(town=["QUEENSTOWN"], flat_model=["MODEL A"], price_psf=500)
	if(len(r) == 87):
		counter += 1

	print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A price_psf=1000")
	r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL A"], price_psf=1000)
	if(len(r) == 6):
		counter += 1

	print()
	print("#" * 30)
	print("Test search with different combinations - two values eac:")
	print("Town - QUEENSTOWN, BUKIT MERAH")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"])
	if(len(r) == 569):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"])
	if(len(r) == 316):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH  flat_model=MODEL A,IMPROVED")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_model=["MODEL A", "IMPROVED"])
	if(len(r) == 440):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH price_psf=900")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], price_psf=900)
	if(len(r) == 174):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM,5 ROOM flat_model=MODEL A,IMPROVED")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"], flat_model=["MODEL A", "IMPROVED"])
	if(len(r) == 266):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM price_psf=900")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"], price_psf=900)
	if(len(r) == 124):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH  flat_model=MODEL A,IMPROVED price_psf=500")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_model=["MODEL A", "IMPROVED"], price_psf=500)
	if(len(r) == 421):
		counter += 1

	print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM flat_model=MODEL A,IMPROVED price_psf=1000")
	r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"], flat_model=["MODEL A", "IMPROVED"], price_psf=1000)
	if(len(r) == 30):
		counter += 1

	#continue to built the test cases on your own.

	#different combination of search to test
	#town - done above
	#town, flat_type - done above
	#town, flat_model - done above
	#town, price_psf - done above

	#town, flat_type, flat_model - done above
	#town, flat_type, price_psf - done above
	#town, flat_model, price_psf - done above

	#town, flat_type, flat_model, price_psf - done above

	#flat_type
	#flat_type, flat_model
	#flat_type, price_psf
	#flat_type, flat_model, price_psf

	#flat_model
	#flat_model,price_psf

	#price_psf

	print("#" * 30)
	print("Test search with no results:")
	print("Town - ABC")
	r = app.search(town=["ABC"])
	if(len(r) == 0):
		counter += 1

	print("Town - QUEENSTOWN flat_type=10 ROOM")
	r = app.search(town=["QUEENSTOWN"], flat_type=["10 ROOM"])
	if(len(r) == 0):
		counter += 1

	print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL D")
	r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL D"])
	if(len(r) == 0):
		counter += 1

	print("Town - QUEENSTOWN  flat_type=4 ROOM flat_model=MODEL A price_psf=2000")
	r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL A"], price_psf=2000)
	if(len(r) == 0):
		counter += 1


	#print(f"Test cases passed:{counter}")


if __name__ == "__main__":
	main()

#Note I did not write the test case for log file:
#The expected output for the log file is
#Log file name: ErrorLog.txt
"""
File line 10: Invalid resale_price:-10.0
File line 11: Invalid floor_area_sqm:BIG
File line 14: Invalid floor_area_sqm:5X
File line 17: Invalid resale_price:-200000.0
File line 21: Invalid resale_price:Expensive
"""

#Note the floor_area in data file is sqm
#the price required is in sqf
#1 sqm = 10.76391041671 sqf

#Expected output
"""
Test get_town():
Test get_flat_type():
Test get_flat_model():
Test search with different combinations - single value each:
Town - QUEENSTOWN
Town - QUEENSTOWN flat_type=4 ROOM
Town - QUEENSTOWN flat_model=MODEL A
Town - QUEENSTOWN price_psf=500
Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A
Town - QUEENSTOWN  flat_type=4 ROOM price_psf=500
Town - QUEENSTOWN flat_model=MODEL A price_psf=500
Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A price_psf=1000

##############################
Test search with different combinations - two values eac:
Town - QUEENSTOWN, BUKIT MERAH
Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM
Town - QUEENSTOWN,BUKIT MERAH  flat_model=MODEL A,IMPROVED
Town - QUEENSTOWN,BUKIT MERAH price_psf=900
Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM,5 ROOM flat_model=MODEL A,IMPROVED
Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM price_psf=900
Town - QUEENSTOWN,BUKIT MERAH  flat_model=MODEL A,IMPROVED price_psf=500
Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM flat_model=MODEL A,IMPROVED price_psf=1000
##############################
Test search with no results:
Town - ABC
Town - QUEENSTOWN flat_type=10 ROOM
Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL D
Town - QUEENSTOWN  flat_type=4 ROOM flat_model=MODEL A price_psf=2000
Test cases passed:23
"""
