// IconValueView.cpp

#include <stdio.h>
#include <string.h>

#include <Bitmap.h>
#include <Region.h>

#include "IconProperty.h"
#include "PropertyItemView.h"

#include "IconValueView.h"

// constructor
IconValueView::IconValueView(IconProperty* property)
	: PropertyItemValueView(property),
	  fProperty(property),
	  fIcon(NULL)
{
	SetFlags(Flags() | B_NAVIGABLE_JUMP);
}

// destructor
IconValueView::~IconValueView()
{
	delete fIcon;
}

// Draw
void
IconValueView::Draw(BRect updateRect)
{
	BRect r;
	BRegion originalClippingRegion;
	GetClippingRegion(&originalClippingRegion);
	if (fIcon) {
		BRect b(Bounds());
		// layout icon in the center
		r = fIcon->Bounds();
		r.OffsetTo(floorf(b.left + b.Width() / 2.0 - r.Width() / 2.0),
				   floorf(b.top + b.Height() / 2.0 - r.Height() / 2.0));
		if (fIcon->ColorSpace() == B_RGBA32 || fIcon->ColorSpace() == B_RGBA32_BIG) {
			// set up transparent drawing and let
			// the base class draw the entire background
			SetHighColor(255, 255, 255, 255);
			SetDrawingMode(B_OP_ALPHA);
			SetBlendingMode(B_PIXEL_ALPHA, B_ALPHA_OVERLAY);
		} else {
			// constrain clipping region to exclude bitmap
			BRegion region = originalClippingRegion;
			region.Exclude(r);
			ConstrainClippingRegion(&region);
		}
	}
	// draw surrouing area (and possibly background for bitmap)
	PropertyItemValueView::Draw(updateRect);

	ConstrainClippingRegion(&originalClippingRegion);
	if (fIcon) {
		DrawBitmap(fIcon, r.LeftTop());
	}
}

// SetIcon
status_t
IconValueView::SetIcon(const unsigned char* bitsFromQuickRes,
					   uint32 width, uint32 height, color_space format)
{
	status_t status = B_BAD_VALUE;
	if (bitsFromQuickRes && width > 0 && height > 0) {
		delete fIcon;
		fIcon = new BBitmap(BRect(0.0, 0.0, width - 1.0, height - 1.0), format);
		status = fIcon ? fIcon->InitCheck() : B_ERROR;
		if (status >= B_OK) {
			// It doesn't look right to copy BitsLength() bytes, but bitmaps
			// exported from QuickRes or WonderBrush still contain their padding,
			// so it is alright.
			memcpy(fIcon->Bits(), bitsFromQuickRes, fIcon->BitsLength());
		} else {
			delete fIcon;
			fIcon = NULL;
			printf("IconValueView::SetIcon() - error allocating bitmap: %s\n", strerror(status));
		}
	}
	return status;
}

// SetToProperty
bool
IconValueView::SetToProperty(const Property* property)
{
	const IconProperty* p = dynamic_cast<const IconProperty*>(property);
	if (p) {
		fProperty->SetMessage(p->Message());
		return true;
	}
	return false;
}


