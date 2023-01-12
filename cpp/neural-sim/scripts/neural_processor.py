import sst

cp0 = sst.Component("cp0", "NeuralProcessor.CommandProcessor")
cp1 = sst.Component("cp1", "NeuralProcessor.CommandProcessor")

cp0.addParams({
    "command_file" : "command.txt"
    })

cp1.addParams({
    "command_file" : "command.txt"
    })


link = sst.Link("component_link")
link.connect( (cp0, "port", "1ns"), (cp1, "port", "1ns") )