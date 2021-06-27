# Weather-Station-Predicts-Rainfall-Intensity
Collates local weather data on Google Sheets and interprets it with a neural network model built w/ TensorFlow to predict rainfall intensity.

Especially in 2020, instant heavy and violent rainfalls have caused detrimental effects on greenhouses and crop yields in my country. Unfortunately, these days unexpected and excessive rainfalls occur more frequently and became relatively common due to climate change in some areas. Meanwhile, other regions suffer from drought. As 2020 passes, more than thirty-five incidents that caused the loss of crops and livestock due to heavy and violent rainfalls are recorded in my region. To contribute to the solution to forfend and avert excessive rainfall instigated problems like agricultural productivity loss, I contemplated this project as a starting point.

Primarily, I focused on excessive rainfall effects on agriculture in this project. However, excessive rainfalls can lead to numerous hazards, for example [1]:

flooding, including risk to human life,

damage to buildings and infrastructure,

loss of crops and livestock,

landslides, which can threaten human life, disrupt transport and communications.

As shown in the latest studies, excessive rainfall can affect crop productivity in various ways, including direct physical damage, delayed planting and harvesting, restricted root growth, oxygen deficiency, and nutrient loss. Thus, too much rain can be as dangerous as drought for agriculture: "Data from the past three decades suggest that excessive rainfall can affect crop yield as much as excessive heat and drought. In a new study, an interdisciplinary team from the University of Illinois linked crop insurance, climate, soil, and corn yield data from 1981 through 2016. The study found that, during some years, excessive rainfall reduced U.S. corn yield by as much as 34% relative to the expected yield. Data suggest that drought and excessive heat caused a yield loss of up to 37% during some years [2]".

Unfortunately, early warning systems are not enough to entirely prevent exacerbating effects of excessive rainfall on agricultural products and processes without adequate and preliminary local weather data for each greenhouse or farm. Therefore, in the hope of averting the detrimental effects of excessive rainfall on agriculture, I decided to create this project as a budget-friendly remote weather station to collect and interpret local weather information to make more accurate predictions on the rainfall intensity.

After doing some research about deep learning and neural networks, I decided to build an artificial neural network (ANN) based on the classification model to interpret the accumulated local weather data to predict the rainfall intensity according to the given classes. As the following study indicates, researchers have applied different neural network models and types to forecast not only rainfalls but also weather phenomena: "Many experiments have used neural networks to predict quantitative rainfall amounts at various locations and look-ahead ranges. For instance, researchers in Thailand were able to obtain highly accurate forecasts using feed-forward neural networks to predict quantitative rainfall amounts in the one to three-hour look-ahead range in order to predict possible flooding dangers. Neural networks have also been used to predict weather phenomena besides the traditional forecast values, such as probability/amount of rainfall, wind speed, barometric pressure, etc. They have been used very successfully to predict tornadoes. Additionally, researchers in Australia successfully used a neural network to identify fog at various forecast ranges ranging from 3 hours to 18 hours around Canberra International Airport [3]."

Before building and testing my neural network model, I had collected weather data at my balcony and backyard in three kilometers radius for more than three months to create a local weather data set showing weather information in my neighborhood. To be able to elicit weather information even in extreme weather conditions, I used a Weather Station Kit with Anemometer, Wind Vane, and Rain Bucket by DFRobot with two different development boards:

NodeMCU ESP-12E (WiFi-Enabled)

Arduino Uno + DFRobot SIM808 GPS/GPRS/GSM Shield (GPRS-Enabled)

Thus, I could transfer weather data via WiFi at my balcony or GPRS if the distance between my router and the weather station is too far away.

I decided to use Google Sheets, a cloud-based spreadsheet program, to collate weather data generated by the weather station because creating big data sets and appending new information are simple with the Google Sheets API. Hence, I developed a web application in PHP to obtain weather data transferred by the development boards and append it to a spreadsheet on Google Sheets.

After completing collecting weather data for more than three months every five minutes, I built an artificial neural network (ANN) model with TensorFlow to make predictions on the rainfall intensity. Theoretically, I assigned a rainfall intensity class for each reading after scaling and normalizing the data set. Then, I trained the neural network model to classify these classes:

No Rainfall

Light Rainfall

Moderate Rainfall

Heavy Rainfall

Violent Rainfall

So, this is my project in a nutshell 😃

You can inspect the project tutorial here:
https://www.hackster.io/kutluhan-aktar/iot-tensorflow-weather-station-predicts-rainfall-intensity-534efe
