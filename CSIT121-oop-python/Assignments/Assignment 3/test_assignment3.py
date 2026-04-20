import csv

#Create ResaleTransaction
class ResaleTransaction:
    def __init__(self, town, flat_type, block, street_name, storey_range, floor_area_sqm, flat_model, lease_commence_date, remaining_lease, resale_price):
        self._town = town
        self._flat_type = flat_type
        self.block = block
        self.street_name = street_name
        self.storey_range = storey_range
        self.floor_area_sqm = float(floor_area_sqm)
        self._flat_model = flat_model
        self.lease_commence_date = int(lease_commence_date)
        self.remaining_lease = remaining_lease
        self.resale_price = float(resale_price)

    @property
    def town(self):
        """Returns the town for this resale transaction."""
        return self._town

    @property
    def flat_type(self):
        """Returns the flat type for this resale transaction."""
        return self._flat_type

    @property
    def flat_model(self):
        """Returns the flat model for this resale transaction."""
        return self._flat_model

    @property
    def price_psf(self):
        """Returns the price per square foot for this resale transaction."""
        # Convert sqm to square feet: 1 sqm = 10.7639 sqft
        floor_area_sqft = self.floor_area_sqm * 10.7639
        return self.resale_price / floor_area_sqft

#create HDB 

class HDB_Resale_Admin:
    def __init__(self):
        self.resales = []  # List to hold ResaleTransaction objects

    def load(self, filename):
        """Load data from a file and handle invalid rows."""
        error_log = []
        line_number = 0  # Track the line number

        try:
            with open(filename, 'r') as file:
                reader = csv.DictReader(file)
                for row in reader:
                    line_number += 1  # Increment line number
                    try:
                        # Validate `resale_price`
                        try:
                            resale_price = float(row['resale_price'])
                            if resale_price < 0:
                                raise ValueError(f"Invalid resale_price:{resale_price}")
                        except ValueError:
                            raise ValueError(f"Invalid resale_price:{row['resale_price']}")

                        # Validate `floor_area_sqm`
                        try:
                            floor_area_sqm = float(row['floor_area_sqm'])
                            if floor_area_sqm < 0:
                                raise ValueError(f"Invalid floor_area_sqm:{floor_area_sqm}")
                        except ValueError:
                            raise ValueError(f"Invalid floor_area_sqm:{row['floor_area_sqm']}")

                        # Create the ResaleTransaction object
                        transaction = ResaleTransaction(
                            town=row['town'],
                            flat_type=row['flat_type'],
                            block=row['block'],
                            street_name=row['street_name'],
                            storey_range=row['storey_range'],
                            floor_area_sqm=floor_area_sqm,
                            flat_model=row['flat_model'],
                            lease_commence_date=int(row['lease_commence_date']),
                            remaining_lease=row['remaining_lease'],
                            resale_price=resale_price
                        )
                        self.resales.append(transaction)

                    except ValueError as e:
                        # Log invalid values or data type issues
                        error_log.append(f"File line {line_number}: {str(e)}")
                    except KeyError as e:
                        # Log missing fields
                        error_log.append(f"File line {line_number}: Missing field: {str(e)}")

        except FileNotFoundError:
            print(f"File not found: {filename}")
            return

        finally:
            # Write error log to a file
            with open("error_log.txt", "w") as log_file:
                for error in error_log:
                    log_file.write(error + "\n")


    def get_town(self):
        """Return a list of distinct towns."""
        return sorted({resale.town for resale in self.resales})

    def get_flat_type(self):
        """Return a list of distinct flat types."""
        return sorted({resale.flat_type for resale in self.resales})

    def get_flat_model(self):
        """Return a list of distinct flat models."""
        return sorted({resale.flat_model for resale in self.resales})

    def search(self, town=None, flat_type=None, flat_model=None, price_psf=None):
        """Search transactions based on given filters."""
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


def check_towns(towns):
    towns_data = ['TOA PAYOH', 'CHOA CHU KANG', 'BUKIT TIMAH', 'YISHUN', 'QUEENSTOWN', 'HOUGANG', 'JURONG WEST', 'WOODLANDS', 'CLEMENTI', 'PUNGGOL', 'BEDOK', 'PASIR RIS', 'BUKIT MERAH', 'SERANGOON', 'MARINE PARADE', 'ANG MO KIO', 'BUKIT PANJANG', 'BUKIT BATOK', 'KALLANG/WHAMPOA', 'BISHAN', 'CENTRAL AREA', 'SEMBAWANG', 'GEYLANG', 'TAMPINES', 'SENGKANG', 'JURONG EAST']
    return set(towns) == set(towns_data)


def check_flat_types(flat_types):
    flat_types_data = ['2 ROOM', '1 ROOM', '4 ROOM', '3 ROOM', '5 ROOM', 'EXECUTIVE', 'MULTI-GENERATION']
    return set(flat_types) == set(flat_types_data)


def check_flat_models(flat_models):
    flat_models_data = ['TYPE S2', 'MODEL A2', '3GEN', 'IMPROVED', 'STANDARD', 'APARTMENT', '2-ROOM', 'MAISONETTE', 'MODEL A-MAISONETTE', 'TYPE S1', 'TERRACE', 'MULTI GENERATION', 'NEW GENERATION', 'PREMIUM APARTMENT LOFT', 'MODEL A', 'SIMPLIFIED', 'DBSS', 'PREMIUM APARTMENT', 'ADJOINED FLAT']
    return set(flat_models) == set(flat_models_data)

#main function
def main():
    counter = 0
    app = HDB_Resale_Admin()
    app.load("Resale2024.csv")
    
    print("Test get_town():")
    if check_towns(app.get_town()):
        counter += 1
        print("pass")
    else:
        print("fail")
    
    print("Test get_flat_type():")
    if check_flat_types(app.get_flat_type()):
        counter += 1
        print("pass")
    else:
        print("fail")
    
    print("Test get_flat_model():")
    if check_flat_models(app.get_flat_model()):
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Test search with different combinations - single value each:")
    print("Town - QUEENSTOWN")
    r = app.search(town=["QUEENSTOWN"])
    if len(r) == 220:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=4 ROOM")
    r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"])
    if len(r) == 83:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_model=MODEL A")
    r = app.search(town=["QUEENSTOWN"], flat_model=["MODEL A"])
    if len(r) == 87:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN price_psf=500")
    r = app.search(town=["QUEENSTOWN"], price_psf=500)
    if len(r) == 202:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A")
    r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL A"])
    if len(r) == 61:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=4 ROOM price_psf=500")
    r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], price_psf=500)
    if len(r) == 82:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_model=MODEL A price_psf=500")
    r = app.search(town=["QUEENSTOWN"], flat_model=["MODEL A"], price_psf=500)
    if len(r) == 87:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A price_psf=1000")
    r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL A"], price_psf=1000)
    if len(r) == 6:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("#" * 30)
    print("Test search with different combinations - two values each:")
    print("Town - QUEENSTOWN, BUKIT MERAH")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"])
    if len(r) == 569:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"])
    if len(r) == 316:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH  flat_model=MODEL A,IMPROVED")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_model=["MODEL A", "IMPROVED"])
    if len(r) == 440:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH price_psf=900")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], price_psf=900)
    if len(r) == 174:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM,5 ROOM flat_model=MODEL A,IMPROVED")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"], flat_model=["MODEL A", "IMPROVED"])
    if len(r) == 266:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM price_psf=900")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"], price_psf=900)
    if len(r) == 124:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH  flat_model=MODEL A,IMPROVED price_psf=500")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_model=["MODEL A", "IMPROVED"], price_psf=500)
    if len(r) == 421:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN,BUKIT MERAH  flat_type=4 ROOM, 5 ROOM flat_model=MODEL A,IMPROVED price_psf=1000")
    r = app.search(town=["QUEENSTOWN", "BUKIT MERAH"], flat_type=["4 ROOM", "5 ROOM"], flat_model=["MODEL A", "IMPROVED"], price_psf=1000)
    if len(r) == 30:
        counter += 1
        print("pass")
    else:
        print("fail")
###############################
#Only flat_type
    print("#" * 30)
    print("Test search with different combinations - flat_type only:")
    print("Flat Type - 4 ROOM")
    r = app.search(flat_type=["4 ROOM"])
    if len(r) == 3925:
        counter += 1
        print("pass")
    else:
        print("fail")

#Flat_type and Flat_model
    print("#" * 30)
    print("Test search with different combinations - flat_type and flat_model:")
    print("Flat Type - 4 ROOM, Flat Model - MODEL A")
    r = app.search(flat_type=["4 ROOM"], flat_model=["MODEL A"])
    if len(r) == 2584:
        counter += 1
        print("pass")
    else:
        print("fail")

#Flat_type and Price_psf
    print("#" * 30)
    print("Test search with different combinations - flat_type and price_psf:")
    print("Flat Type - 4 ROOM, Price PSF >= 500")
    r = app.search(flat_type=["4 ROOM"], price_psf=500)
    if len(r) == 2859:
        counter += 1
        print("pass")
    else:
        print("fail")

#Flat_type , flat_model and price_psf
    print("#" * 30)
    print("Test search with different combinations - flat_type, flat_model, and price_psf:")
    print("Flat Type - 4 ROOM, Flat Model - MODEL A, Price PSF >= 1000")
    r = app.search(flat_type=["4 ROOM"], flat_model=["MODEL A"], price_psf=1000)
    if len(r) == 57:
        counter += 1
        print("pass")
    else:
        print("fail")
#Flat_model 
    print("#" * 30)
    print("Test search with different combinations - flat_type only:")
    print("Flat Model - MODEL A, Price PSF >= 1000")
    r = app.search(flat_model=["MODEL A"])
    if len(r) == 3661:
        counter += 1
        print("pass")
    else:
        print("fail")
#Flat_model and price_psf
    print("#" * 30)
    print("Test search with different combinations - flat_type, price_psf:")
    print("Flat Model - MODEL A, Price PSF >= 1000")
    r = app.search(flat_model=["MODEL A"], price_psf=1000)
    if len(r) == 86:
        counter += 1
        print("pass")
    else:
        print("fail")

#price_psf

    print("#" * 30)
    print("Test search with price_psf:")


    print("Price_psf=500")
    r = app.search(price_psf=500)
    if len(r) == 6579:
        counter += 1
        print("pass")
    else:
        print("fail")
#No result
    print("#" * 30)
    print("Test search with no results:")
    print("Town - ABC")
    r = app.search(town=["ABC"])
    if len(r) == 0:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=10 ROOM")
    r = app.search(town=["QUEENSTOWN"], flat_type=["10 ROOM"])
    if len(r) == 0:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL D")
    r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL D"])
    if len(r) == 0:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("Town - QUEENSTOWN flat_type=4 ROOM flat_model=MODEL A price_psf=2000")
    r = app.search(town=["QUEENSTOWN"], flat_type=["4 ROOM"], flat_model=["MODEL A"], price_psf=2000)
    if len(r) == 0:
        counter += 1
        print("pass")
    else:
        print("fail")

    print("#" * 30)
    print("Test cases passed:", counter)


if __name__ == "__main__":
    main()

