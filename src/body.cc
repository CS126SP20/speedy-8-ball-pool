//
// Created by lilyl on 4/19/2020.
//

#include "mylibrary/body.h"

namespace myapp {
    Body::Body(myapp::BodyRef body, gl::Texture2dRef texture, vec2 pos)
        : body_(body), texture_(texture), pos_(pos)
    {
        if(body_)
            body_->SetUserData(this);
    }
}