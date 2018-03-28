print("hello from lua!");
Ent = cTypes.Entity.new();
transMgr:addTo(Ent,Transform(0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9));
transMgr:printTableContents();
