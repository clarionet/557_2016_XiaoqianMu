#include "ObjectIdFactory.h"
#include <math.h>

ObjectId* ObjectIdFactory::getId() {
    int rW = floor(current_id / 100) ;
    int gW = floor((current_id - rW*100)/10);
    int bW = floor((current_id - rW*100 - gW*10));
    ObjectId *newId = new ObjectId();
    newId->r = rW*0.1;
    newId->g = gW*0.1;
    newId->b = bW*0.1;
    newId->id = current_id;

    // cout << rW << gW << bW;

    current_id++;

    return newId;
}

int ObjectIdFactory::getIdFromColor(float col[4]) {
    // cout << col[0] << col[1] <<col[2]<<endl;
    return round(col[0] * 10) * 100 + round(col[1]*10)*10 + round(col[2] * 10);
}
