import sst

cp = sst.Component("cp", "NeuralProcessor.CommandProcessor")
compcore = sst.Component("compcore", "NeuralProcessor.CompCore")

cp.addParams({
    "command_file" : "command.txt"
    })


link = sst.Link("component_link")
link.connect( (cp, "port", "10s"), (compcore, "port", "10s") )