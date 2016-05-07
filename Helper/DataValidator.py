

#Errror flags

FOREST_NOT_TRAINED=1
NO_TEST_DATA =2
OK =0

class DataValidator(object):
    
    
    @staticmethod
    def validate_dataset(dataset):
        """
        Error validator for input data, make sure it is 2d  numpy (ndarray) data, dataset not empty
        @param dataset: input dataset either training or testing 

        """
        if type(dataset) is not np.ndarray:
            raise NameError("Dataset is not in ndarray format")
        #check for size of dataset return for 0 size 
        if len(dataset)<1:
            raise NameError("Data is empty")
    @staticmethod
    def validate_model(error_flag):
        if error_flag==OK:
            return True
        if error_flag==NO_TEST_DATA:
            raise NameError("No test data given to the model (test function not called)")
        if error_flag==FOREST_NOT_TRAINED:
            raise NameError("train function net yet called")
