// Saturation.h

#ifndef SATURATION_H
#define SATURATION_H

#include "FilterObject.h"

class Saturation : public FilterObject {
 public:
								Saturation();
								Saturation(const Saturation& other);
								Saturation(BMessage* archive);
	virtual						~Saturation();

	virtual	Stroke*				Clone() const;
	virtual	bool				SetTo(const Stroke* from);

								// BArchivable protocoll
	virtual	status_t			Archive(BMessage* into, bool deep = true) const;
	static	BArchivable*		Instantiate(BMessage* archive);

	virtual	void				ProcessBitmap(BBitmap* bitmap,
											  BBitmap* alphaBitmap,
											  BRect constrainRect) const;

	virtual	PropertyObject*		MakePropertyObject() const;
	virtual	bool				SetToPropertyObject(PropertyObject* object);

 protected:
			BBitmap*			_LuminanceBitmap(const BBitmap* bitmap) const;

			float				fSaturation;
};

#endif	// SATURATION_H
