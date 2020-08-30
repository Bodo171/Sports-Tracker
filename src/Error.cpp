#include "Error.h"

Error::Error(string message) {
    messageToDisplay = message;
}
string Error::getErrorMessage() {
    return messageToDisplay;
}